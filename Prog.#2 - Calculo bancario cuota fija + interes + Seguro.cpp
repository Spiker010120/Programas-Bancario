#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <windows.h>
#include <algorithm>
#include <cctype>

using namespace std;

// ============================================================
//                    COLORES DE CONSOLA
// ============================================================

void color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

const int AZUL = 9;
const int CIAN = 11;
const int VERDE = 10;
const int AMARILLO = 14;
const int ROJO = 12;
const int BLANCO = 15;
const int GRIS = 8;

// ============================================================
//                    DATOS DEL CLIENTE
// ============================================================

string nombre;
string cedula;
string telefono;

double monto = 0;
double tasa = 0;
double seguro = 0;
double cargo = 0;
double itbis = 0;
double cuota = 0;

int meses = 0;

// ============================================================
//                    FUNCIONES GENERALES
// ============================================================

void limpiarEntrada()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pausa()
{
    color(CIAN);
    cout << "\n   Presione ENTER para continuar...";
    color(BLANCO);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void linea()
{
    color(AZUL);
    cout << "============================================================\n";
    color(BLANCO);
}

void lineaCorta()
{
    color(CIAN);
    cout << "------------------------------------------------------------\n";
    color(BLANCO);
}

// ============================================================
//                    ENCABEZADO
// ============================================================

void encabezado(string titulo)
{
    system("cls");

    cout << "\n";

    color(AZUL);

    cout << "============================================================\n";
    cout << "||                                                        ||\n";

    color(CIAN);
    cout << "||              BANCO DIGITAL RD                         ||\n";

    color(AZUL);
    cout << "||                                                        ||\n";
    cout << "============================================================\n";

    color(AMARILLO);
    cout << "                 " << titulo << "\n";

    color(AZUL);
    cout << "============================================================\n";

    color(BLANCO);
}

// ============================================================
//                    CALCULAR CUOTA
// ============================================================

double calcularCuota()
{
    double i = tasa / 100.0 / 12.0;

    if (i == 0)
        return monto / meses;

    double factor = pow(1 + i, meses);

    return monto * (i * factor) / (factor - 1);
}

// ============================================================
//                    NUEVA SIMULACION
// ============================================================

void simulacion()
{
    system("cls");

    encabezado("NUEVA SIMULACION DE PRESTAMO");

    color(CIAN);
    cout << "\n   DATOS DEL CLIENTE\n";
    lineaCorta();

    color(BLANCO);

    limpiarEntrada();

    cout << "   Nombre completo : ";
    getline(cin, nombre);

    cout << "   Cedula          : ";
    getline(cin, cedula);

    cout << "   Telefono        : ";
    getline(cin, telefono);

    color(CIAN);
    cout << "\n   DATOS DEL PRESTAMO\n";
    lineaCorta();

    color(BLANCO);

    cout << "   Monto del prestamo       : RD$ ";
    cin >> monto;

    cout << "   Tasa de interes anual    : ";
    cin >> tasa;

    cout << "   Cantidad de meses        : ";
    cin >> meses;

    cout << "   Seguro mensual           : RD$ ";
    cin >> seguro;

    cout << "   Cargo/impuesto mensual   : RD$ ";
    cin >> cargo;

    // ========================================================
    //                    ITBIS OPCIONAL
    // ========================================================

    char deseaItbis;

    cout << "\n   Desea agregar ITBIS [S/N]: ";
    cin >> deseaItbis;

    deseaItbis = toupper(deseaItbis);

    if (deseaItbis == 'S')
    {
        cout << "   Porcentaje de ITBIS       : ";
        cin >> itbis;
    }
    else if (deseaItbis == 'N')
    {
        itbis = 0;
    }
    else
    {
        system("cls");

        color(ROJO);
        cout << "\n   ERROR: Debe seleccionar S o N.\n";
        color(BLANCO);

        limpiarEntrada();
        pausa();
        return;
    }

    // ========================================================
    // VALIDACIONES
    // ========================================================

    if (cin.fail())
    {
        system("cls");

        color(ROJO);
        cout << "\n   ERROR: Debe introducir valores numericos validos.\n";
        color(BLANCO);

        limpiarEntrada();
        pausa();
        return;
    }

    if (monto <= 0)
    {
        system("cls");

        color(ROJO);
        cout << "\n   ERROR: El monto debe ser mayor que RD$ 0.00.\n";
        color(BLANCO);

        pausa();
        return;
    }

    if (tasa < 0)
    {
        system("cls");

        color(ROJO);
        cout << "\n   ERROR: La tasa no puede ser negativa.\n";
        color(BLANCO);

        pausa();
        return;
    }

    if (meses <= 0)
    {
        system("cls");

        color(ROJO);
        cout << "\n   ERROR: La cantidad de meses debe ser mayor que 0.\n";
        color(BLANCO);

        pausa();
        return;
    }

    if (seguro < 0 || cargo < 0)
    {
        system("cls");

        color(ROJO);
        cout << "\n   ERROR: Seguro y cargos no pueden ser negativos.\n";
        color(BLANCO);

        pausa();
        return;
    }

    if (itbis < 0 || itbis > 100)
    {
        system("cls");

        color(ROJO);
        cout << "\n   ERROR: El ITBIS debe estar entre 0% y 100%.\n";
        color(BLANCO);

        pausa();
        return;
    }

    // ========================================================
    // CALCULO
    // ========================================================

    cuota = calcularCuota();

    double intereses = (cuota * meses) - monto;
    double totalSeguro = seguro * meses;
    double totalCargo = cargo * meses;

    double subtotal = monto + intereses + totalSeguro + totalCargo;

    double totalItbis = subtotal * (itbis / 100.0);

    double total = subtotal + totalItbis;

    // ========================================================
    // RESULTADO
    // ========================================================

    system("cls");

    encabezado("RESULTADO DE LA SIMULACION");

    color(VERDE);
    cout << "\n   SIMULACION COMPLETADA CORRECTAMENTE\n";
    color(BLANCO);

    cout << "\n";

    linea();

    color(CIAN);
    cout << "                    RESUMEN\n";

    color(BLANCO);

    lineaCorta();

    cout << fixed << setprecision(2);

    cout << "   Monto solicitado       : RD$ " << monto << "\n";
    cout << "   Tasa anual             : " << tasa << "%\n";
    cout << "   Plazo                  : " << meses << " meses\n";

    lineaCorta();

    cout << "   Cuota fija mensual     : RD$ " << cuota << "\n";
    cout << "   Total intereses        : RD$ " << intereses << "\n";
    cout << "   Total seguro           : RD$ " << totalSeguro << "\n";
    cout << "   Total cargos/impuestos : RD$ " << totalCargo << "\n";

    if (itbis > 0)
    {
        cout << "   ITBIS (" << itbis << "%)          : RD$ "
             << totalItbis << "\n";
    }

    cout << "   Subtotal               : RD$ " << subtotal << "\n";

    lineaCorta();

    color(VERDE);
    cout << "   TOTAL A PAGAR          : RD$ " << total << "\n";

    color(BLANCO);

    linea();

    pausa();
}

// ============================================================
//                    TABLA DE AMORTIZACION
// ============================================================

void amortizacion()
{
    system("cls");

    if (monto <= 0)
    {
        color(ROJO);
        cout << "\n   Primero debes realizar una simulacion.\n";
        color(BLANCO);

        pausa();
        return;
    }

    encabezado("TABLA DE AMORTIZACION");

    double saldo = monto;
    double interesMensual = tasa / 100.0 / 12.0;

    cout << "\n";

    color(CIAN);
    cout << "   CLIENTE: ";
    color(BLANCO);
    cout << nombre << "\n";

    color(CIAN);
    cout << "   PRESTAMO: RD$ ";
    color(BLANCO);
    cout << fixed << setprecision(2) << monto << "\n";

    color(CIAN);
    cout << "   TASA: ";
    color(BLANCO);
    cout << tasa << "% anual\n";

    color(CIAN);
    cout << "   PLAZO: ";
    color(BLANCO);
    cout << meses << " meses\n";

    if (itbis > 0)
    {
        color(CIAN);
        cout << "   ITBIS: ";
        color(BLANCO);
        cout << itbis << "%\n";
    }

    cout << "\n";

    color(AZUL);
    cout << "================================================================================\n";

    color(AMARILLO);

    cout << left
         << setw(6) << "No."
         << setw(15) << "Capital"
         << setw(15) << "Interes"
         << setw(13) << "Seguro"
         << setw(13) << "Cargo"
         << setw(13) << "ITBIS"
         << setw(15) << "Cuota"
         << setw(15) << "Saldo"
         << "\n";

    color(AZUL);
    cout << "================================================================================\n";

    color(BLANCO);

    for (int n = 1; n <= meses; n++)
    {
        double interes = saldo * interesMensual;
        double capital = cuota - interes;

        if (interesMensual == 0)
        {
            interes = 0;
            capital = cuota;
        }

        if (n == meses)
        {
            capital = saldo;
        }

        if (capital > saldo)
            capital = saldo;

        saldo -= capital;

        if (saldo < 0.01)
            saldo = 0;

        double cuotaBase = capital + interes + seguro + cargo;

        double itbisMensual = cuotaBase * (itbis / 100.0);

        double cuotaTotal = cuotaBase + itbisMensual;

        cout << fixed << setprecision(2);

        cout << left
             << setw(6) << n
             << setw(15) << capital
             << setw(15) << interes
             << setw(13) << seguro
             << setw(13) << cargo
             << setw(13) << itbisMensual
             << setw(15) << cuotaTotal
             << setw(15) << saldo
             << "\n";
    }

    color(AZUL);
    cout << "================================================================================\n";

    color(VERDE);
    cout << "\n   Tabla generada correctamente.\n";

    color(BLANCO);

    pausa();
}

// ============================================================
//                    FACTURA
// ============================================================

void factura()
{
    system("cls");

    if (monto <= 0)
    {
        color(ROJO);
        cout << "\n   Primero debes realizar una simulacion.\n";
        color(BLANCO);

        pausa();
        return;
    }

    encabezado("FACTURA BANCARIA");

    double intereses = (cuota * meses) - monto;
    double totalSeguro = seguro * meses;
    double totalCargo = cargo * meses;

    double subtotal = monto + intereses + totalSeguro + totalCargo;

    double totalItbis = subtotal * (itbis / 100.0);

    double total = subtotal + totalItbis;

    cout << "\n";

    color(CIAN);
    cout << "                 BANCO DIGITAL RD\n";

    color(BLANCO);
    cout << "                 FACTURA DE PRESTAMO\n";

    linea();

    cout << fixed << setprecision(2);

    color(AMARILLO);
    cout << "   INFORMACION DEL CLIENTE\n";
    color(BLANCO);

    lineaCorta();

    cout << "   Nombre       : " << nombre << "\n";
    cout << "   Cedula       : " << cedula << "\n";
    cout << "   Telefono     : " << telefono << "\n";

    color(AMARILLO);
    cout << "\n   DETALLES DEL PRESTAMO\n";
    color(BLANCO);

    lineaCorta();

    cout << "   Monto        : RD$ " << monto << "\n";
    cout << "   Tasa anual   : " << tasa << "%\n";
    cout << "   Plazo        : " << meses << " meses\n";

    color(AMARILLO);
    cout << "\n   COSTOS DEL PRESTAMO\n";
    color(BLANCO);

    lineaCorta();

    cout << "   Cuota fija   : RD$ " << cuota << "\n";
    cout << "   Intereses    : RD$ " << intereses << "\n";
    cout << "   Seguro       : RD$ " << totalSeguro << "\n";
    cout << "   Cargos       : RD$ " << totalCargo << "\n";

    if (itbis > 0)
    {
        cout << "   ITBIS (" << itbis << "%) : RD$ "
             << totalItbis << "\n";
    }

    cout << "   Subtotal     : RD$ " << subtotal << "\n";

    lineaCorta();

    color(VERDE);
    cout << "   TOTAL A PAGAR: RD$ " << total << "\n";

    color(BLANCO);

    linea();

    color(GRIS);
    cout << "   Documento generado por Banco Digital RD\n";
    cout << "   Simulacion educativa de calculo financiero\n";

    color(BLANCO);

    linea();

    pausa();
}

// ============================================================
//                    MENU PRINCIPAL
// ============================================================

void menu()
{
    int opcion;

    do
    {
        system("cls");

        color(AZUL);

        cout << "\n";
        cout << "============================================================\n";
        cout << "||                                                        ||\n";

        color(CIAN);
        cout << "||              BANCO DIGITAL RD                         ||\n";

        color(AZUL);
        cout << "||                                                        ||\n";
        cout << "============================================================\n";

        color(AMARILLO);
        cout << "                 SISTEMA DE PRESTAMOS\n";

        color(AZUL);
        cout << "============================================================\n";

        color(CIAN);

        cout << "\n";
        cout << "             +----------------------------------+\n";
        cout << "             |         MENU PRINCIPAL           |\n";
        cout << "             +----------------------------------+\n";

        color(BLANCO);

        cout << "             |                                  |\n";

        color(VERDE);
        cout << "             |   [1]  Nueva simulacion          |\n";

        color(CIAN);
        cout << "             |   [2]  Tabla de amortizacion     |\n";

        color(AMARILLO);
        cout << "             |   [3]  Factura del cliente       |\n";

        color(ROJO);
        cout << "             |   [4]  Salir                     |\n";

        color(CIAN);
        cout << "             |                                  |\n";
        cout << "             +----------------------------------+\n";

        color(BLANCO);

        cout << "\n";
        cout << "             Seleccione una opcion: ";

        cin >> opcion;

        if (cin.fail())
        {
            limpiarEntrada();

            system("cls");

            color(ROJO);
            cout << "\n             ERROR: Debe introducir un numero.\n";
            color(BLANCO);

            pausa();
            continue;
        }

        switch (opcion)
        {
            case 1:
                simulacion();
                break;

            case 2:
                amortizacion();
                break;

            case 3:
                factura();
                break;

            case 4:

                system("cls");

                color(CIAN);

                cout << "\n";
                cout << "============================================================\n";
                cout << "||                                                        ||\n";

                color(VERDE);
                cout << "||       GRACIAS POR UTILIZAR BANCO DIGITAL RD           ||\n";

                color(CIAN);
                cout << "||                                                        ||\n";
                cout << "============================================================\n";

                color(BLANCO);

                break;

            default:

                system("cls");

                color(ROJO);
                cout << "\n             ERROR: Opcion no valida.\n";
                color(BLANCO);

                pausa();
        }

    } while (opcion != 4);
}

// ============================================================
//                    PROGRAMA PRINCIPAL
// ============================================================

int main()
{
    SetConsoleTitle("Banco Digital RD - Sistema de Prestamos");

    color(BLANCO);

    system("cls");

    menu();

    return 0;
}
