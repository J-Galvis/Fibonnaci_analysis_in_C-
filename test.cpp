#include <iostream>
#include <fstream>
#include <chrono>
#include <gmp.h>
#include <string>

using namespace std;

void guardarCSV(string data, float time,string location){

    // Abre el archivo en modo append
    ofstream outFile(location, ios::app);

    // Escribe los datos en el formato CSV
    outFile << data << "," << time << endl;

    // Cierra el archivo
    outFile.close();
    cout << data << endl;

}

// Function to compute the nth Fibonacci number using recursion
void fibonacci(mpz_t *result, int n) {
    if (n <= 0) {
        mpz_set_ui(*result, 0); // Fibonacci(0) = 0
    } else if (n == 1) {
        mpz_set_ui(*result, 1); // Fibonacci(1) = 1
    } else {
        mpz_t a, b;
        mpz_init(a);
        mpz_init(b);

        // Recursive calls to compute Fibonacci(n-1) and Fibonacci(n-2)
        fibonacci(&a, n - 1);
        fibonacci(&b, n - 2);

        // Fibonacci(n) = Fibonacci(n-1) + Fibonacci(n-2)
        mpz_add(*result, a, b);

        // Clean up temporary mpz_t variables
        mpz_clear(a);
        mpz_clear(b);
    }
}

int main() {
    for (int n = 50; n < 100; n++)
    {
        mpz_t result;
        mpz_init(result);

        // Compute the nth Fibonacci number using the recursive function
        auto comienza = chrono::high_resolution_clock::now();
        fibonacci(&result, n);
        auto termina = chrono::high_resolution_clock::now();
        auto tiempo = chrono::duration_cast<std::chrono::milliseconds>(termina - comienza);
        float time = tiempo.count();

        // Print the result
        string str = mpz_get_str(NULL, 10, result);
        guardarCSV(str,time,"Recurcividad.csv");
        cout << str;
        mpz_clear(result);
    }
    return 0;
}