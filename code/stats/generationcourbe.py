import pandas as pd

import matplotlib.pyplot as plt

def plot_csv_data(file_path):
    data = pd.read_csv(file_path)

    if data.shape[1] < 3:
        raise ValueError("Le fichier CSV doit contenir au moins 3 colonnes.")

    etape = data.iloc[:, 0]
    popLapin = data.iloc[:, 1]
    popRenard = data.iloc[:, 2]

    # Plot the data
    plt.figure(figsize=(10, 6))
    plt.plot(etape, popLapin, label='Population lapin')
    plt.plot(etape, popRenard, label='Population renard')
    plt.xlabel('Temps')
    plt.ylabel('Population')
    plt.title('Evolution des populations de lapins et de renards')
    plt.legend()
    plt.grid(True)
    #plt.show()


    output_file = "courbes.png"
    plt.savefig(output_file)
    print(f"Graphique sauvegardé dans {output_file}")

plot_csv_data("data.csv")