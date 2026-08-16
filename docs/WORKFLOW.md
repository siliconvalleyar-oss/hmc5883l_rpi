# WORKFLOW.md

## Workflow

### 1. Desarrollo Local (Desktop)
Editar código en el proyecto local. Usar `make USE_STUB=1` para compilar sin hardware bcm2835.

### 2. Push a GitHub
```bash
git add -A
git commit -m "mensaje"
git push origin master
```

### 3. Deploy en Raspberry Pi
```bash
ssh joy@raspberry.local "cd /home/joy/src/hmc5883l_rpi && git pull && make clean && make -j4 && sudo make run"
```

### 4. Compilación Nativa en Raspberry Pi
```bash
cd /home/joy/src/hmc5883l_rpi
sudo ./scripts/install_deps.sh
make clean && make -j4
sudo ./bin/App
```

### 5. Verificar Arquitectura
```bash
make arch
```

### Notas
- El Makefile detecta automáticamente `aarch64`, `armv7l`, `armv6l` y no aplica `-m64` ni `-m32` en ARM.
- Si el binario falla con `x86_64-binfmt-P`, significa que se compiló en otra arquitectura. Hacer `make clean && make` en la Pi.
