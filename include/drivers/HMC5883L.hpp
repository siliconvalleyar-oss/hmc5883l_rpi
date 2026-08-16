#ifndef HMC5883L_HPP_
#define HMC5883L_HPP_

#include <cstdint>
#include <array>

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
        bcm2835_spi_setCSPolarity(BCM2835_SPI_CS_LOW);

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
        uint8_t value = 0;
        bcm2835_spi_transfer(reinterpret_cast<char*>(&addr), reinterpret_cast<char*>(&value), 1);
        return value;
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
        uint8_t buf[2];
        buf[0] = reg;  // bit7 = 0 for write
        buf[1] = value;
        bcm2835_spi_transfer(reinterpret_cast<char*>(buf), nullptr, 2);
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

#endif
