#include <stdio.h>
#include <string.h>

typedef void (*apf[])(unsigned char, char *);

void dummy(unsigned char num, char *cadena) {
    (void)num;
    (void)cadena;
}

void unidades(unsigned char num, char *cadena) {
    char *numero[] = {
        "", "uno", "dos", "tres", "cuatro", "cinco",
        "seis", "siete", "ocho", "nueve"
    };
    strcat(cadena, numero[num%10]);
}

void decena(unsigned char num, char *cadena) {
    char *numero[] = {
        "diez", "once", "doce", "trece", "catorce", "quince",
        "dieciseis", "diecisiete", "dieciocho", "diecinueve"
    };
    strcpy(cadena, numero[num%10]);
}

void conector_veintena(unsigned char num, char *cadena) {
    char *conector[] = {
        "", "\bi", "\bi", "\bi", "\bi", "\bi",
        "\bi", "\bi", "\bi", "\bi"
    };
    strcat(cadena, conector[num%10]);
    unidades(num, cadena);
}

void conector_xtena(unsigned char num, char *cadena) {
    char *conector[] = {
        "", " y ",  " y ", " y ", " y ",
        " y ", " y ", " y ", " y ", " y "
    };
    strcat(cadena, conector[num%10]);
    unidades(num, cadena);
}

void conector(unsigned char num, char *cadena) {
    (apf) {
        dummy, dummy, conector_veintena, conector_xtena, conector_xtena, conector_xtena,
        conector_xtena, conector_xtena, conector_xtena, conector_xtena
    }[num/10](num, cadena);
}

void xtenas(unsigned char num, char *cadena) {
    char *numero[] = {
        "", "", "veinte", "treinta", "cuarenta", "cincuenta",
        "sesenta", "setenta", "ochenta", "noventa"
    };
    strcpy(cadena, numero[num/10]);
    conector(num, cadena);
}

void centena_0(unsigned char num, char *cadena) {
    (apf) {
        unidades, decena, xtenas, xtenas, xtenas,
        xtenas, xtenas, xtenas, xtenas, xtenas
    }[num/10](num, cadena);
}

void centena_10(unsigned char num, char *cadena) {
    char *numero[] = {
        "cien", "", "", "", "",
        "", "", "", "", ""
    };
    strcpy(cadena, numero[num%10]);
}

void centena_1(unsigned char num, char *cadena) {
    (apf) {
        centena_10, dummy, dummy, dummy, dummy,
        dummy, dummy, dummy, dummy, dummy
    }[num/10](num, cadena);
}

char* num2str(unsigned char num) {
    static char numero[25];
    numero[0] = '\0';
    (apf){centena_0, centena_1, dummy}[num/100](num, numero);
    return numero;
}

int main() {
    for(int i=1; i<=100; ++i)
        printf("%s\n", num2str(i));
}
