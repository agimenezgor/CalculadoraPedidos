#pragma once
#define MAX_DESIGNACION 40
#define MAX_REFERENCIAS 100
#define MAX_CHARS 15


typedef struct {
	char designacion[MAX_DESIGNACION] = "";
	char numero[MAX_CHARS] = "";
	char codicionante[MAX_CHARS] = "";
	char facingMaximo[MAX_CHARS] = "";
	char ventas[MAX_CHARS] = "";
}tReferencia;

struct tProveedor {
	char designacion[MAX_DESIGNACION] = "";
	char numero[MAX_CHARS] = "";
	char franco[MAX_CHARS] = "";
	char diasServicio[MAX_CHARS] = "";
	char pedMaximo[MAX_CHARS] = "";
	char calculo[MAX_CHARS] = "";
};

typedef struct {
	char auxdesignacion[40] = "";
	int auxcondicionante;
	float auxventas;
	float diascubiertos;
	int stockactual;
	int contador = 0;
	char auxnumero[12] = "";
}tAuxCalculo;
