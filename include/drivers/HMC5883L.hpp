#ifndef HMC5883L_HPP_
#define HMC5883L_HPP_

#include <cstdint>
#include <array>
#include <memory>
#include <iostream>
#include <cmath>
#include <ctime>
#include <unistd.h>

#ifdef HAS_BCM2835
#include <bcm2835.h>
#else
#include "libraries/bcm2835_stub.hpp"
#endif

class HMC5883L {
public:
    enum class Gain : uint8_t {
        G_0_88 = 0x00,  // 0.88 Ga, 1370 LSB/G
        G_1_3  = 0x20,  // 1.3 Ga, 1090 LSB/G (default)
        G_1_9  = 0x40,  // 1.9 Ga, 820 LSB/G
        G_2_5  = 0x60,  // 2.5 Ga, 660 LSB/G
        G_4_0  = 0x80,  // 4.0 Ga, 440 LSB/G
        G_4_7  = 0xA0,  // 4.7 Ga, 390 LSB/G
        G_5_6  = 0xC0,  // 5.6 Ga, 330 LSB/G
        G_8_1  = 0xE0   // 8.1 Ga, 230 LSB/G
    };

    enum class DataRate : uint8_t {
        HZ_0_75 = 0x00,
        HZ_1_5  = 0x04,
        HZ_3_0  = 0x08,
        HZ_7_5  = 0x0C,
        HZ_15   = 0x10,
        HZ_30   = 0x14,
        HZ_75   = 0x18
    };

    enum class SamplesAvg : uint8_t {
        SAMPLES_1 = 0x00,
        SAMPLES_2 = 0x01,
        SAMPLES_4 = 0x02,
        SAMPLES_8 = 0x03
    };

    enum class Mode : uint8_t {
        IDLE        = 0x03,
        SINGLE_SHOT = 0x01,
        CONTINUOUS  = 0x00
    };

    struct MagData {
        int16_t x;
        int16_t y;
        int16_t z;
    };

    HMC5883L(uint8_t cs = BCM2835_SPI_CS0)
        : m_cs(cs), m_gain(Gain::G_1_3), m_lsb_per_gauss(1090.0f) {}

    bool begin() {
        if (!bcm2835_init()) {
            return false;
        }
        bcm2835_spi_begin();
        bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
        bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
        bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64);
        bcm2835_spi_chipSelect(m_cs);
        bcm2835_spi_setChipSelectPolarity(m_cs, 0);

        if (!isConnected()) {
            end();
            return false;
        }

        uint8_t id_a = readReg(0x07);
        uint8_t id_b = readReg(0x08);
        uint8_t id_c = readReg(0x09);

        if (id_a != 0x48 || id_b != 0x34 || id_c != 0x33) {
            end();
            return false;
        }

        setGain(m_gain);
        setDataRate(DataRate::HZ_15);
        setSamplesAvg(SamplesAvg::SAMPLES_8);
        setMode(Mode::CONTINUOUS);
        bcm2835_delay(100);

        return true;
    }

    void end() {
        bcm2835_spi_end();
        bcm2835_close();
    }

    bool isConnected() const {
        uint8_t id_a = readReg(0x07);
        uint8_t id_b = readReg(0x08);
        uint8_t id_c = readReg(0x09);
        return (id_a == 0x48 && id_b == 0x34 && id_c == 0x33);
    }

    void setGain(Gain gain) {
        m_gain = gain;
        writeReg(0x0B, static_cast<uint8_t>(gain));
        updateGainScale();
        bcm2835_delay(1);
    }

    void setDataRate(DataRate rate) {
        uint8_t config_a = readReg(0x0A);
        config_a &= ~0x1C;
        config_a |= static_cast<uint8_t>(rate);
        writeReg(0x0A, config_a);
    }

    void setSamplesAvg(SamplesAvg samples) {
        uint8_t config_a = readReg(0x0A);
        config_a &= ~0x03;
        config_a |= static_cast<uint8_t>(samples);
        writeReg(0x0A, config_a);
    }

    void setMode(Mode mode) {
        writeReg(0x0C, static_cast<uint8_t>(mode));
    }

    MagData readData() {
        MagData data = {0, 0, 0};
        std::array<uint8_t, 6> buf;
        readRegisters(0x00, buf.data(), buf.size());

        data.x = static_cast<int16_t>((buf[0] << 8) | buf[1]);
        data.z = static_cast<int16_t>((buf[2] << 8) | buf[3]);
        data.y = static_cast<int16_t>((buf[4] << 8) | buf[5]);

        return data;
    }

    bool isDataReady() const {
        return (readReg(0x06) & 0x01) != 0;
    }

    void calibrate(uint16_t samples = 100) {
        MagData sum = {0, 0, 0};
        for (uint16_t i = 0; i < samples; ++i) {
            MagData d = readData();
            sum.x += d.x;
            sum.y += d.y;
            sum.z += d.z;
            bcm2835_delay(10);
        }
        m_offset.x = sum.x / samples;
        m_offset.y = sum.y / samples;
        m_offset.z = sum.z / samples;
    }

    float getGaussX(int16_t raw) const {
        return (raw - m_offset.x) / m_lsb_per_gauss;
    }

    float getGaussY(int16_t raw) const {
        return (raw - m_offset.y) / m_lsb_per_gauss;
    }

    float getGaussZ(int16_t raw) const {
        return (raw - m_offset.z) / m_lsb_per_gauss;
    }

private:
    uint8_t m_cs;
    Gain m_gain;
    float m_lsb_per_gauss;
    MagData m_offset = {0, 0, 0};

    uint8_t readReg(uint8_t reg) const {
        uint8_t addr = static_cast<uint8_t>(0x80) | reg;
        bcm2835_spi_transfer(addr);
        return bcm2835_spi_transfer(0x00);
    }

    void readRegisters(uint8_t reg, uint8_t* buf, uint32_t len) const {
        uint8_t tx[7] = {0};
        uint8_t rx[7] = {0};
        tx[0] = static_cast<uint8_t>(0x80) | reg;
        for (uint32_t i = 1; i <= len; ++i) {
            tx[i] = 0xFF;
        }
        bcm2835_spi_transfernb(reinterpret_cast<char*>(tx), reinterpret_cast<char*>(rx), len + 1);
        for (uint32_t i = 0; i < len; ++i) {
            buf[i] = rx[i + 1];
        }
    }

    void writeReg(uint8_t reg, uint8_t value) const {
        bcm2835_spi_transfer(reg);
        bcm2835_spi_transfer(value);
    }

    void updateGainScale() {
        switch (m_gain) {
            case Gain::G_0_88: m_lsb_per_gauss = 1370.0f; break;
            case Gain::G_1_3:  m_lsb_per_gauss = 1090.0f; break;
            case Gain::G_1_9:  m_lsb_per_gauss =  820.0f; break;
            case Gain::G_2_5:  m_lsb_per_gauss =  660.0f; break;
            case Gain::G_4_0:  m_lsb_per_gauss =  440.0f; break;
            case Gain::G_4_7:  m_lsb_per_gauss =  390.0f; break;
            case Gain::G_5_6:  m_lsb_per_gauss =  330.0f; break;
            case Gain::G_8_1:  m_lsb_per_gauss =  230.0f; break;
        }
    }
};

namespace app {

class Hmc5883l_t {
public:
    Hmc5883l_t(uint8_t cs = BCM2835_SPI_CS0) : m_cs(cs), m_simulated(false), m_last_heading(0.0f) {
        m_last_data.x = 0;
        m_last_data.y = 0;
        m_last_data.z = 0;
    }

    ~Hmc5883l_t() {
        stop();
    }

    bool start() {
        m_driver = std::make_unique<HMC5883L>(m_cs);
        if (!m_driver->begin()) {
            std::cout << "[HMC5883L] Sensor not detected. Continuing in SIMULATED mode." << std::endl;
            m_simulated = true;
        } else {
            std::cout << "[HMC5883L] Sensor detected. Calibrating..." << std::endl;
            m_driver->calibrate(100);
            std::cout << "[HMC5883L] Calibration complete." << std::endl;
        }
        m_running = true;
        return true;
    }

    void run() {
        if (!start()) {
            return;
        }

        std::cout << "[HMC5883L] Running. Press Ctrl+C to stop." << std::endl;

        time_t last_print = 0;
        while (m_running) {
            process();
            time_t now = time(nullptr);
            if (now != last_print) {
                last_print = now;
                printMeasurements();
            }
            usleep(50000);
        }
    }

    void stop() {
        if (!m_running) {
            return;
        }
        m_running = false;
        if (m_driver && !m_simulated) {
            m_driver->end();
        }
        std::cout << "[HMC5883L] Stopped." << std::endl;
    }

    HMC5883L::MagData getMagData() const {
        return m_last_data;
    }

    float getHeading() const {
        return m_last_heading;
    }

    bool isSimulated() const {
        return m_simulated;
    }

private:
    void process() {
        if (m_simulated) {
            simulateData();
            return;
        }

        if (!m_driver || !m_driver->isDataReady()) {
            return;
        }

        HMC5883L::MagData data = m_driver->readData();
        float bx = m_driver->getGaussX(data.x);
        float by = m_driver->getGaussY(data.y);
        m_last_data = data;
        m_last_heading = std::atan2(by, bx) * 180.0f / 3.14159265f;
        if (m_last_heading < 0.0f) {
            m_last_heading += 360.0f;
        }
    }

    void simulateData() {
        static float phase = 0.0f;
        phase += 0.02f;
        if (phase > 360.0f) {
            phase -= 360.0f;
        }

        float heading = phase + (std::sin(phase * 0.1f) * 10.0f);
        if (heading < 0.0f) {
            heading += 360.0f;
        }
        if (heading >= 360.0f) {
            heading -= 360.0f;
        }

        m_last_heading = heading;
        m_last_data.x = static_cast<int16_t>(std::cos(heading * 3.14159265f / 180.0f) * 500);
        m_last_data.y = static_cast<int16_t>(std::sin(heading * 3.14159265f / 180.0f) * 500);
        m_last_data.z = static_cast<int16_t>(std::sin(heading * 0.8f) * 300);
    }

    void printMeasurements() const {
        std::cout << "=== Measurements ===" << std::endl;
        std::cout << "X: " << m_last_data.x
                  << "  Y: " << m_last_data.y
                  << "  Z: " << m_last_data.z << std::endl;
        std::cout << "Heading: " << static_cast<int>(std::round(m_last_heading)) << " deg" << std::endl;
    }

    uint8_t m_cs;
    bool m_running;
    bool m_simulated;
    std::unique_ptr<HMC5883L> m_driver;
    HMC5883L::MagData m_last_data;
    float m_last_heading;
};

}

#endif
