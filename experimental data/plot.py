import os
import pandas as pd
import matplotlib.pyplot as plt

# Configuración base
base_dir = "."
carpetas_algoritmos = {
    "Memo": "memo_times",
    "DP": "dp_times",
    "DP-Opt": "dpOpt_times",
}

# Almacenar los promedios
promedios = {}

rec_path = os.path.join(base_dir, "rec_t1_t2.csv")
if os.path.exists(rec_path):
    df_rec = pd.read_csv(rec_path)
    if not df_rec.empty and "tiempo_segundos" in df_rec.columns:
        transicion = "t1_t2"
        if transicion not in promedios:
            promedios[transicion] = {}
        promedios[transicion]["Recursivo"] = df_rec["tiempo_segundos"].mean()

# Leer y calcular promedios
for nombre_algo, carpeta in carpetas_algoritmos.items():
    carpeta_path = os.path.join(base_dir, carpeta)
    if not os.path.isdir(carpeta_path):
        continue

    for archivo in os.listdir(carpeta_path):
        if archivo.endswith(".csv"):
            partes = archivo.replace(".csv", "").split("_")
            if len(partes) < 3:
                continue
            transicion = "_".join(partes[1:])  # ej: t1_t2
            archivo_path = os.path.join(carpeta_path, archivo)

            df = pd.read_csv(archivo_path)
            if df.empty or "tiempo_segundos" not in df.columns:
                continue

            tiempo_promedio = df["tiempo_segundos"].mean()

            if transicion not in promedios:
                promedios[transicion] = {}
            promedios[transicion][nombre_algo] = tiempo_promedio


# Convertir a DataFrame para graficar
df_promedios = pd.DataFrame(promedios).T  # transiciones como índice
df_promedios = df_promedios.sort_index()

# Crear gráfico de barras agrupadas con escala logarítmica
colores = {
    'DP': '#1f77b4',
    'DP-Opt': "#00a156ff",
    'Memo': "#f17108",
    'Recursivo': '#d62728'
}

df_promedios.plot(kind='bar', figsize=(12, 6), color=[colores[col] for col in df_promedios.columns])
plt.title("Tiempos promedio por transición y algoritmo")
plt.ylabel("Tiempo promedio (segundos, escala logarítmica)")
plt.xlabel("Transición")
plt.yscale("log")
plt.xticks(rotation=45)
plt.legend(title="Algoritmo")
plt.tight_layout()

# Guardar gráfico
plt.savefig("grafico_promedios_log.png")
plt.show()
print(df_promedios.columns.tolist())

