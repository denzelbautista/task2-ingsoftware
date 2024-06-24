# Ingeniería de Software - Tarea 2 - Smart Net Solutions

## Creacion del entorno virtual

Para la creación del entorno virtual se utilizó el siguiente comando:

```bash
python3 -m venv .venv
```

## Activación del entorno virtual

Para activar el entorno virtual se utilizó el siguiente comando:

```bash
source venv/bin/activate # ubuntu
```
```bash	
source venv/Scripts/activate # windows
```

## Instalación de dependencias

Para instalar las dependencias se utilizó el siguiente comando:

```bash
pip install -r requirements.txt
```

## Ejecución de la aplicación

Para ejecutar la aplicación se utilizó el siguiente comando:

```bash
uvicorn main:app --reload
```

