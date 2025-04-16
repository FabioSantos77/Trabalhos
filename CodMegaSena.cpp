//FELLYPE LUZ E SILVA
//FABIO EDUARDO ALI DOS SANTOS
//KAIKE CHAVES DA SILVA
#include<stdio.h>
#include<stdlib.h>
#include<conio2.h>
#include<ctype.h>
#include<string.h>
#include<time.h>
#include<windows.h>

#define TFC 30
#define TFA 50
#define TFAP 50
#define TFS 5

void SetColor(int textColor, int backgroundColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (backgroundColor << 4) | textColor);
}

struct ConcursoPremiado 
{
    int ConcursoNum;
    int QtdeApostadoresPremiados;
};
struct Terno
{
	int ConcursoTerno,ApostaTerno;
};
struct Quadra
{
	int ConcursoQuadra,ApostaQuadra;
};
struct Quina
{
	int ConcursoQuina,ApostaQuina;
};
struct Apostado
{
	int Num;
	int Quantidade;	
};
struct Sorteado
{
	int Num;
	int Quantidade;	
};
struct	TpConc
{
	int NumConc, NumSort[5], dia, mes, ano;
};

struct TpApostadores
{
	char CPF[15],Nome[30], Fone[12];
};

struct TpApostas
{
	int NumAposta,QtdeNumApostado,NumApostado[10];
	int NmeroConc;//Chave estrangeira
	char CPFApostador[15]; //Chave estrangeira
};

void Moldura (int CI, int LI, int CF, int LF)
{
    gotoxy(CI,LI);
    printf("%c",201);
    
    gotoxy(CI,LF);
    printf("%c", 200);
    
    gotoxy(CF,LI);
    printf("%c",187);
    
    gotoxy(CF,LF);
    printf("%c",188);
    
    for(int i = CI+1;i<CF;i++)
    {
    	gotoxy(i,LI);
    	printf("%c", 205);
    	gotoxy(i,LF);
    	printf("%c",205);
    }
    for(int i = LI+1;i<LF;i++)
    {
    	gotoxy(CI,i);
    	printf("%c", 186);
    	gotoxy(CF,i);
    	printf("%c",186);
    }
}
char MenuConcurso(void)
{
    clrscr();
    SetColor(10, 0);

    Moldura(30, 3, 90, 25);

    gotoxy(35, 4); printf("[A] Cadastro de Concurso");
    gotoxy(35, 5); printf("[B] Consulta de Concurso");
    gotoxy(35, 6); printf("[C] Alteracao de Concurso");
    gotoxy(35, 7); printf("[D] Exclusao de Concurso");

    gotoxy(35, 9);
    printf("Opcao desejada: ");

    char opcao = toupper(getche());

    SetColor(15, 0);

    return opcao;
}

char MenuApostador(void)
{
    clrscr();
    SetColor(10, 0);

    Moldura(30, 3, 90, 25);

    gotoxy(35, 4); printf("[A] Cadastro de Apostador");
    gotoxy(35, 5); printf("[B] Consulta de Apostador");
    gotoxy(35, 6); printf("[C] Alteracao de Apostador");
    gotoxy(35, 7); printf("[D] Exclusao de Apostador");

    gotoxy(35, 9);
    printf("Opcao desejada: ");

    char opcao = toupper(getche());

    SetColor(15, 0);

    return opcao;
}

char MenuAposta(void)
{
    clrscr();
    SetColor(10, 0);

    Moldura(30, 3, 90, 25);

    gotoxy(35, 4); printf("[A] Cadastro de Aposta");
    gotoxy(35, 5); printf("[B] Consulta de Aposta");
    gotoxy(35, 6); printf("[C] Alteracao de Aposta");
    gotoxy(35, 7); printf("[D] Exclusao de Aposta");

    gotoxy(35, 9);
    printf("Opcao desejada: ");

    char opcao = toupper(getche());

    SetColor(15, 0);

    return opcao;
}
char Menu(void)
{
    SetColor(10, 0);  // Texto verde e fundo preto

    Moldura(30, 3, 90, 25); // Moldura com os limites

    // Centralizando as opções diretamente
    gotoxy(45, 5); printf("[A] Menu de Concurso");
    gotoxy(45, 6); printf("[B] Menu de Apostador");
    gotoxy(45, 7); printf("[C] Menu de Aposta");
    gotoxy(45, 8); printf("[D] Verificacao de varias apostas");
    gotoxy(45, 9); printf("[E] Relatorio");
    gotoxy(45, 10); printf("[F] Resumo dos apostadores premiados");
    gotoxy(45, 11); printf("[G] 5 Numero mais sorteado");
    gotoxy(45, 12); printf("[H] 5 Numero menos sorteado");
    gotoxy(45, 13); printf("[I] 5 Numero mais apostado");
    gotoxy(45, 14); printf("[J] 5 Numero menos apostado");
    gotoxy(45, 15); printf("[K] Validacao das Apostas");
    gotoxy(45, 16); printf("[L] Ganhadores por numeros no concurso");
    gotoxy(45, 17); printf("[ESC] Finalizar");
    gotoxy(45, 18); printf("[Z] Mostrar numeros sorteados");

    gotoxy(45, 19);  // Ajustando para a linha correta para a entrada da opção
    printf("Opcao desejada: ");

    char opcao = toupper(getche());

    SetColor(15, 0);  // Resetando para cor padrão

    return opcao;
}


int VerificaTerno(TpApostas Aposta, TpConc Concurso) 
{
    int acertos = 0;
    for (int i = 0; i < Aposta.QtdeNumApostado; i++) 
        for (int j = 0; j < 5; j++) 
            if (Aposta.NumApostado[i] == Concurso.NumSort[j]) 
                acertos++;
    return (acertos == 3); 
}

int VerificaQuadra(TpApostas Aposta, TpConc Concurso) 
{
    int acertos = 0;
    for (int i = 0; i < Aposta.QtdeNumApostado; i++) 
        for (int j = 0; j < 5; j++) 
            if (Aposta.NumApostado[i] == Concurso.NumSort[j]) 
                acertos++;
    return (acertos == 4); 
}

int VerificaQuina(TpApostas Aposta, TpConc Concurso) 
{
    int acertos = 0;
    for (int i = 0; i < Aposta.QtdeNumApostado; i++) 
        for (int j = 0; j < 5; j++) 
            if (Aposta.NumApostado[i] == Concurso.NumSort[j]) 
                acertos++;
    return (acertos == 5);  
}
void EXIApostadores(TpApostadores Apostadores[TFA], int TLA, int Pos)
{
    clrscr();
    SetColor(10, 0);

    Moldura(30, 3, 90, 25);

    gotoxy(35, 4); printf("Nome: ");
    gotoxy(35, 5); puts(Apostadores[Pos].Nome);

    gotoxy(35, 6); printf("CPF: ");
    gotoxy(35, 7); puts(Apostadores[Pos].CPF);

    gotoxy(35, 8); printf("Telefone: ");
    gotoxy(35, 9); puts(Apostadores[Pos].Fone);

    SetColor(15, 0);
}

int BuscaConcurso(TpConc Con[TFC], int TLC, int Num)
{
	int i = 0;
	while(i < TLC && Num != Con[i].NumConc)
		i++;
	if(i < TLC)
		return i;	//Achou retorna posição
	else
		return -1;	// Não achou retorna -1
}
int BuscaApostadores(TpApostadores Apostadores[TFA],int TLA, char CPF[15])
{
	int i=0;
	if (TLA == 0)
		return i;
	else
		while(i <TLA && strcmp(CPF,Apostadores[i].CPF) != 0)
			i++;
	return i;
}

int BuscaAposta(TpApostas Aposta[TFAP],int TLAP, int NumeroAposta)
{
	int i=0;
	while(i < TLAP && NumeroAposta != Aposta[i].NumAposta)
		i++;
	if(i < TLAP)
		return i;	//Achou retorna posição
	else
		return -1;	// Não achou retorna -1	
}
int BuscaSorteio(int numeros[],int tamanho,int valor)
{
	int i;
    for (int i = 0; i < TFS; i++) 
	{
        if (numeros[i] == valor) 
		{
            return i; // Número já foi sorteado
        }
    }
    return -1; // Número ainda não foi sorteado
}

//			ALTERAÇÕES DO TpConc
void CADConcurso(TpConc CadConcurso[TFC], int &TLC, int NumeroMaisSorteado[60]) {
    int pos = 0, Num = 0, repetido = 0, max = 60;
    int NumSort[TFS], i, j, TLS = 0, Aux;
    int AuxDia, AuxMes, AuxAno;

    do {
        clrscr();  // Limpar a tela antes de redesenhar a moldura
        Moldura(30, 3, 90, 25); // Moldura com os limites

        // Mensagem centralizada
        gotoxy(35, 4); 
        printf("Cadastro de Concurso");
		if(Num == 0)
		{
			gotoxy(35, 5);
        	printf("Digite o Numero do Concurso: ");
        	scanf("%d", &Num);
		}
        // Verificar se o número do concurso já existe
        pos = BuscaConcurso(CadConcurso, TLC, Num);
        while (pos != -1) {
            gotoxy(35, 6);
            printf("Numero de Concurso ja Cadastrado!");
            Num = 0;
            while (Num <= 0) {
                gotoxy(35, 7);
                printf("Digite o Numero do Concurso: ");
                scanf("%d", &Num);
            }
            pos = BuscaConcurso(CadConcurso, TLC, Num);
        }
        CadConcurso[TLC].NumConc = Num;
        gotoxy(35, 8);
        printf("Numero do Concurso Cadastrado!");
        fflush(stdin);

        // Cadastro da Data
        gotoxy(35, 9);
        printf("Digite a Data Do Concurso:");
        gotoxy(35, 10);
        printf("Dia: ");
        scanf("%d", &AuxDia);
        while (AuxDia < 1 || AuxDia > 31) {
            gotoxy(35, 11);
            printf("Dia Invalido! Digite novamente: ");
            scanf("%d", &AuxDia);
        }
        CadConcurso[TLC].dia = AuxDia;

        gotoxy(35, 12);
        printf("Mes: ");
        scanf("%d", &AuxMes);
        while (AuxMes < 1 || AuxMes > 12) {
            gotoxy(35, 13);
            printf("Mes Invalido! Digite novamente: ");
            scanf("%d", &AuxMes);
        }
        CadConcurso[TLC].mes = AuxMes;

        gotoxy(35, 14);
        printf("Ano (2025-2030): ");
        scanf("%d", &AuxAno);
        while (AuxAno < 2025 || AuxAno > 2030) {
            gotoxy(35, 15);
            printf("Ano Invalido! Digite novamente: ");
            scanf("%d", &AuxAno);
        }
        CadConcurso[TLC].ano = AuxAno;
        fflush(stdin);
        gotoxy(35, 16);
        printf("Data Cadastrada!");

        // Sorteio dos números
        gotoxy(35, 17);
        printf("Sorteando numeros...");
        for (i = 0; i < TFS; i++) {
            do {
                Aux = (rand() % max) + 1;
                pos = (i == 0) ? -1 : BuscaSorteio(NumSort, i, Aux);
            } while (pos != -1);

            NumSort[i] = Aux;
            CadConcurso[TLC].NumSort[i] = Aux;
            NumeroMaisSorteado[Aux - 1]++;
        }

        TLC++;

        gotoxy(35, 18);
        printf("Digite o Numero do Concurso: ");
        scanf("%d", &Num);

    } while (TLC < TFC && Num != 0);
}

    	//for (int i = 0; i < TOTAL_NUMEROS; i++) {
        //printf("%d ", Num[i]);
	
void CONSConcurso(TpConc Concurso[TFC], int TLC)
{
    clrscr();
    SetColor(12, 0);
    Moldura(30, 3, 90, 25);

    int i, AuxNum = 0, pos = 0;

    gotoxy(35, 4);
    printf("- - - CONSULTA - - -");
    gotoxy(35, 5);
    printf("Digite o Numero do Concurso: ");
    scanf("%d", &AuxNum);
    
    pos = BuscaConcurso(Concurso, TLC, AuxNum);

    if (pos != -1) {
        gotoxy(35, 7);
        printf("Numero do Concurso: %d", Concurso[pos].NumConc);
        gotoxy(35, 8);
        printf("Data: %d/%d/%d", Concurso[pos].dia, Concurso[pos].mes, Concurso[pos].ano);
        
        for (i = 0; i < TFS; i++) {
            gotoxy(35, 9 + i);
            printf("Numero Sorteado: %d", Concurso[pos].NumSort[i]);
        }
        getch();
    } else 
	{
        gotoxy(35, 7);
        printf("Concurso nao encontrado!");
    }
    getch();

    SetColor(15, 0);
}
void ALTConcurso(TpConc Concurso[TFC], int &TLC)
{
    int AuxNum, pos = 0, opcao = 0;
    int AuxDia = 0, AuxMes = 0, AuxAno = 0;
    
    clrscr();
    SetColor(12, 0);
    Moldura(30, 3, 90, 25);

    gotoxy(35, 4);
    printf("- - - ALTERACAO - - -");
    gotoxy(35, 5);
    printf("Digite o Numero do Concurso: ");
    scanf("%d", &AuxNum);
    
    pos = BuscaConcurso(Concurso, TLC, AuxNum);
    
    if (pos >= 0 && AuxNum != 0)
    {   
        gotoxy(35, 10);
        printf("Digite o que deseja alterar: ");
        gotoxy(35, 11);
        printf("[1] - Numero do Concurso (Nao Permitido) ");
        gotoxy(35, 12);
        printf("[2] - Data do Concurso ");
        gotoxy(35, 13);
        printf("[3] - Numeros Sorteados do Concurso ");
        gotoxy(35, 14);
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao)
        {
            case 1:
                gotoxy(35, 16);
                printf("Nao e possivel alterar esse campo!");
                break;
                
            case 2:
                gotoxy(35, 16);
                printf("Digite a nova data do concurso:");
                
                do {
                    gotoxy(35, 17);
                    printf("Dia: ");
                    scanf("%d", &AuxDia);
                    if (AuxDia < 1 || AuxDia > 31)
                        printf("Dia invalido! Tente novamente.\n");
                } while (AuxDia < 1 || AuxDia > 31);
                
                do {
                    gotoxy(35, 18);
                    printf("Mes: ");
                    scanf("%d", &AuxMes);
                    if (AuxMes < 1 || AuxMes > 12)
                        printf("Mes invalido! Tente novamente.\n");
                } while (AuxMes < 1 || AuxMes > 12);
                
                do {
                    gotoxy(35, 19);
                    printf("Ano (2025-2030): ");
                    scanf("%d", &AuxAno);
                    if (AuxAno < 2025 || AuxAno > 2030)
                        printf("Ano invalido! Digite um ano entre 2025 e 2030.\n");
                } while (AuxAno < 2025 || AuxAno > 2030);
                
                Concurso[pos].dia = AuxDia;
                Concurso[pos].mes = AuxMes;
                Concurso[pos].ano = AuxAno;
                
                gotoxy(35, 20);
                printf("Data alterada com sucesso!");
                break;
                
            case 3:
                gotoxy(35, 16);
                printf("Nao e possivel alterar esse campo.");
                break;
        }
    }
    else
    {
        gotoxy(35, 7);
        printf("Concurso nao encontrado!");
    }

    getch();
    SetColor(15, 0);
}
void EXCLConcurso(TpConc Concurso[TFC], int &TLC, TpApostas Apostas[TFAP], int TLAP)
{
    int AuxNum, pos, posAposta, i;
    char confirma;

    clrscr();
    SetColor(12, 0);
    Moldura(30, 3, 90, 25);

    gotoxy(35, 4);
    printf("- - - EXCLUSAO - - -");
    gotoxy(35, 5);
    printf("Digite o Numero do Concurso: ");
    scanf("%d", &AuxNum);
    
    pos = BuscaConcurso(Concurso, TLC, AuxNum);
    
    if (pos >= 0) {
        posAposta = BuscaAposta(Apostas, TLAP, AuxNum);

        if (posAposta != -1) {
            gotoxy(35, 7);
            printf("Este concurso nao pode ser excluido, pois existem");
            gotoxy(35,8);
			printf("apostas associadas a ele!");
        } else {
            gotoxy(35, 7);
            printf("Tem certeza que deseja excluir a data e os numeros");
            gotoxy(35,8);
			printf("sorteados deste concurso? (S/N): ");
            scanf(" %c", &confirma);
            
            if (confirma == 'S' || confirma == 's') {
                Concurso[pos].dia = 0;
                Concurso[pos].mes = 0;
                Concurso[pos].ano = 0;
                
                for (i = 0; i < TFS; i++) {
                    Concurso[pos].NumSort[i] = 0; // Zera os números sorteados
                }
                
                gotoxy(35, 9);
                printf("Dados excluidos com sucesso!");
                TLC--;
            } else {
                gotoxy(35, 9);
                printf("Operacao cancelada!");
            }
        }
    } else 
	{
        gotoxy(35, 7);
        printf("Concurso nao encontrado!");
    }
    
    getch();
    SetColor(15, 0);
}
// 			ALTERAÇÕES DO TpApostadores

void CADApostadores(TpApostadores Apostadores[TFA], int &TLA) {
    char Opcao, Maioridade, CPF[15];

    do {
        clrscr();
        Moldura(30, 3, 90, 25); // Moldura com os limites
        gotoxy(35, 4);
        printf("### Cadastro de Apostadores ###");

        gotoxy(35, 6);
        printf("Deseja realizar um cadastro?[S] - Sim[N] - Nao");
        Opcao = getch();

        while (toupper(Opcao) == 'S') {
            clrscr();
            Moldura(30, 3, 90, 25); // Moldura com os limites
            gotoxy(35, 4);
            printf("Cadastro de Apostador");

            gotoxy(35, 6);
            printf("Voce e maior de idade?[S] - Sim[N] - Nao");
            Maioridade = getch();

            switch (toupper(Maioridade)) {
                case 'S':
                    clrscr();
                    Moldura(30, 3, 90, 25); // Moldura com os limites
                    gotoxy(35, 4);
                    printf("Cadastro de Apostador");

                    gotoxy(35, 6);
                    printf("Digite seu CPF: ");
                    fflush(stdin);
                    gets(CPF);

                    gotoxy(35, 8);
                    printf("***Seu CPF e: ");
                    puts(CPF);

                    if (BuscaApostadores(Apostadores, TLA, CPF) == TLA && strlen(CPF) > 0) {
                        strcpy(Apostadores[TLA].CPF, CPF);

                        do {
                            gotoxy(35, 10);
                            printf("Digite seu nome: ");
                            fflush(stdin);
                            gets(Apostadores[TLA].Nome);
                        } while (strlen(Apostadores[TLA].Nome) < 1);

                        do {
                            gotoxy(35, 12);
                            printf("Digite seu numero de telefone: ");
                            fflush(stdin);
                            gets(Apostadores[TLA].Fone);
                        } while (strlen(Apostadores[TLA].Fone) < 1);

                        TLA++;

                        gotoxy(35, 14);
                        printf("Apostador cadastrado com sucesso!");
                        getch();
                        clrscr();

                        Moldura(30, 3, 90, 25); // Moldura com os limites
                        gotoxy(35, 4);
                        printf("Cadastro de Apostador");

                        gotoxy(35, 6);
                        printf("Deseja realizar um novo cadastro?[S] - Sim[N] - Nao");
                        Opcao = getch();
                    } else {
                        clrscr();
                        Moldura(30, 3, 90, 25); // Moldura com os limites
                        gotoxy(35, 4);
                        printf("Erro no Cadastro");

                        gotoxy(35, 6);
                        printf("*** O CPF informado nao pode ser cadastrado! ***");
                        getch();
                    }
                    break;

                case 'N':
                    clrscr();
                    Moldura(30, 3, 90, 25); // Moldura com os limites
                    gotoxy(35, 4);
                    printf("Cadastro de Apostador");

                    gotoxy(35, 6);
                    printf("Voce nao pode realizar o cadastro!");
                    Opcao = 'N';
                    Sleep(2000);
                    break;
            }
        }

    } while (toupper(Opcao) == 'S');
}
void CONSApostadores(TpApostadores Apostadores[TFA], int TLA)
{
    char Opcao, CPF[15];
    int Pos;

    clrscr();
    Moldura(30, 3, 90, 25); // Moldura com os limites
    gotoxy(35, 4);
    printf("### Consulta de Apostadores ###");

    gotoxy(35, 6);
    printf("Deseja realizar uma consulta?[S] - Sim[N] - Nao");
    Opcao = getch();

    while (toupper(Opcao) == 'S') {
        clrscr();
        Moldura(30, 3, 90, 25); // Moldura com os limites
        gotoxy(35, 4);
        printf("Consulta de Apostador");

        gotoxy(35, 6);
        printf("Digite o CPF que deseja buscar: ");
        gets(CPF);
        clrscr();

        if (BuscaApostadores(Apostadores, TLA, CPF) < TLA) {
            Pos = BuscaApostadores(Apostadores, TLA, CPF);
            Moldura(30, 3, 90, 25); // Moldura com os limites
            gotoxy(35, 4);
            printf("### CPF encontrado! ###");

            EXIApostadores(Apostadores, TLA, Pos);
        } else {
            Moldura(30, 3, 90, 25); // Moldura com os limites
            gotoxy(35, 4);
            printf("CPF nao encontrado!");
        }

        gotoxy(35, 10);
        printf("Deseja Buscar por outro CPF?[S] - Sim[N] - Nao");
        Opcao = getch();
    }
}

void ALTApostadores(TpApostadores Apostadores[TFA], int TLA)
{
    int Pos;
    char Opcao, Nome[30], CPF[15], Fone[12];

    clrscr();
    Moldura(30, 3, 100, 25); // Moldura com os limites
    gotoxy(35, 4);
    printf("### Alteracao de Apostadores ###");

    gotoxy(35, 6);
    printf("Deseja realizar uma alteracao?[S] - Sim[N] - Nao");
    Opcao = getch();

    while (toupper(Opcao) == 'S') {
        clrscr();
        Moldura(30, 3, 100, 25); // Moldura com os limites
        gotoxy(35, 4);
        printf("Alteracao de Apostadores");

        gotoxy(35, 6);
        printf("Digite o CPF do usuario que deseja realizar a alteracao: ");
        gets(CPF);
        clrscr();

        if (BuscaApostadores(Apostadores, TLA, CPF) < TLA) {
            Pos = BuscaApostadores(Apostadores, TLA, CPF);
            Moldura(30, 3, 100, 25); // Moldura com os limites
            gotoxy(35, 4);
            printf("### Alteracao de Apostadores ###");

           

            gotoxy(35, 6);
            printf("Qual parametro deseja alterar?");
            gotoxy(35, 7);
			printf("[N] - Nome");
			gotoxy(35, 8);
			printf("[T] - Telefone");
            Opcao = getch();

            if (toupper(Opcao) == 'N') {
                gotoxy(35, 9);
                printf("Digite o novo nome: ");
                gets(Nome);
                strcpy(Apostadores[Pos].Nome, Nome);
            }
            if (toupper(Opcao) == 'T') {
                gotoxy(35, 10);
                printf("Digite o novo numero de telefone: ");
                gets(Fone);
                strcpy(Apostadores[Pos].Fone, Fone);
            } else {
                gotoxy(35, 11);
                printf("Opcao invalida!");
            }

            clrscr();
            Moldura(30, 3, 100, 25); // Moldura com os limites
            gotoxy(35, 4);
            printf("### Alteracao concluida com sucesso! ###");

            EXIApostadores(Apostadores, TLA, Pos);
            getch();

            clrscr();
            Moldura(30, 3, 100, 25); // Moldura com os limites
            gotoxy(35, 4);
            printf("### Alteracao de Apostadores ###");

            gotoxy(35, 6);
            printf("Deseja realizar uma alteracao?[S] - Sim[N] - Nao");
            Opcao = getch();
        } else {
            Moldura(30, 3, 100, 25); // Moldura com os limites
            gotoxy(35, 4);
            printf("CPF nao encontrado!");
            Sleep(2000);
        }
    }
}

void LISApostadores(TpApostadores Apostadores[TFA], int TLA)
{
    int i = 0;

    clrscr();
    Moldura(30, 3, 90, 25); // Moldura com os limites
    gotoxy(35, 4);
    printf("### Listagem de Apostadores ###");

    for (i = 0; i < TLA; i++) {
        clrscr();
        Moldura(30, 3, 90, 25); // Moldura com os limites
        gotoxy(35, 4);
        printf("### Apostador - %d ###", i + 1);

        gotoxy(35, 6);
        printf("Nome: ");
        puts(Apostadores[i].Nome);

        gotoxy(35, 8);
        printf("CPF: ");
        puts(Apostadores[i].CPF);

        gotoxy(35, 10);
        printf("Telefone: ");
        puts(Apostadores[i].Fone);

        getch();
    }
}

void EXCLApostadores(TpApostadores Apostadores[TFA], int &TLA)
{
    int Pos, i = 0;
    char Opcao, CPF[15];

    clrscr();
    Moldura(30, 3, 90, 25); // Moldura com os limites
    gotoxy(35, 4);
    printf("### Exclusao de Apostadores ###");

    gotoxy(35, 6);
    printf("Deseja realizar uma exclusao?");
    gotoxy(35,7);
	printf("[S] - Sim[N] - Nao");
    Opcao = getch();

    while (toupper(Opcao) == 'S') {
        clrscr();
        Moldura(30, 3, 90, 25); // Moldura com os limites
        gotoxy(35, 4);
        printf("### Exclusao de Apostadores ###");

        gotoxy(35, 6);
        printf("Digite o CPF do apostador que deseja excluir: ");
        gets(CPF);

        if (BuscaApostadores(Apostadores, TLA, CPF) < TLA) {
            Pos = BuscaApostadores(Apostadores, TLA, CPF);
            clrscr();

            Moldura(30, 3, 90, 25); // Moldura com os limites
            gotoxy(35, 4);
            printf("### Exclusao Concluida ###");

            for (i = Pos; i < TLA - 1; i++) {
                strcpy(Apostadores[i].CPF, Apostadores[i + 1].CPF);
                strcpy(Apostadores[i].Nome, Apostadores[i + 1].Nome);
                strcpy(Apostadores[i].Fone, Apostadores[i + 1].Fone);
            }
            TLA--;
            gotoxy(35, 6);
            printf("Apostador excluido com sucesso!");
            Sleep(2000);
        } else {
            gotoxy(35, 6);
            printf("CPF nao encontrado!");
            Sleep(2000);
        }

        clrscr();
        Moldura(30, 3, 90, 25); // Moldura com os limites
        gotoxy(35, 4);
        printf("### Exclusao de Apostadores ###");

        gotoxy(35, 6);
        printf("Deseja realizar uma exclusao?[S] - Sim[N] - Nao");
        Opcao = getch();
    }

    gotoxy(35, 8);
    printf("Operacao finalizada!");
    getch();
}
//			ALTERAÇÕES DO TpApostas

void CADApostas(TpApostas CadApostas[TFAP], int &TLAP, TpConc Concurso[TFC], int TLC, TpApostadores Apostador[TFA], int TLA, int NumeroMaisApostado[60])
{
    int pos = 0, NumConc = 0, NumAposta = 0, QtdeApostada, NumApostado[10];
    char CPF[15], opc;
    
    clrscr();
    if (TLA == 0)
    {
    	Moldura(30, 3, 90, 25);
        gotoxy(35, 10);
        printf("Nenhum CPF cadastrado");
        getch();
    }
    else
    {
        Moldura(30, 3, 90, 25); // Moldura com os limites
        gotoxy(35, 4);
        printf("### Cadastro de apostas ###");

        gotoxy(35, 5);
        printf("Numero da aposta para cadastro: ");
        scanf("%d", &NumAposta);

        while (TLAP < TFAP && NumAposta > 0)
        {
            if (TLAP != 0)
            {
                pos = BuscaAposta(CadApostas, TLAP, NumAposta);
                while (pos != -1)
                {
                    gotoxy(35, 6);
                    printf("Numero da aposta ja cadastrado");
                    NumAposta = 0;
                    while (NumAposta == 0)
                    {
                        gotoxy(35, 7);
                        printf("Digite outro numero: ");
                        scanf("%d", &NumAposta);
                        pos = BuscaAposta(CadApostas, TLAP, NumAposta);
                    }
                }
            }
            Moldura(30, 3, 90, 25); 
			CadApostas[TLAP].NumAposta = NumAposta;
            gotoxy(35, 8);
            printf("Numero da aposta cadastrado.");

            gotoxy(35, 9);
            printf("Numero do CPF do apostador: ");
            fflush(stdin); gets(CPF);
            pos = BuscaApostadores(Apostador, TLA, CPF);
            while (pos == TLA)
            {
                gotoxy(35, 10);
                printf("CPF nao encontrado");
                gotoxy(35, 11);
                printf("Digite outro CPF: ");
                fflush(stdin); gets(CPF);
                pos = BuscaApostadores(Apostador, TLA, CPF);
            }
            strcpy(CadApostas[TLAP].CPFApostador, CPF);
            gotoxy(35, 12);
            printf("CPF encontrado e cadastrado");

            gotoxy(35, 13);
            printf("Numero do concurso apostado: ");
            scanf("%d", &NumConc);
            pos = BuscaConcurso(Concurso, TLC, NumConc);
            while (pos == -1)
            {
                gotoxy(35, 14);
                printf("Numero do concurso nao encontrado");
                gotoxy(35, 15);
                printf("Digite outro numero: ");
                scanf("%d", &NumConc);
                pos = BuscaConcurso(Concurso, TLC, NumConc);
            }
            gotoxy(35, 16);
            printf("Numero do concurso encontrado e cadastrado");
            CadApostas[TLAP].NmeroConc = NumConc;

            gotoxy(35, 17);
            printf("Quantidade de numero apostado: ");
            scanf("%d", &QtdeApostada);
            while (QtdeApostada < 5 || QtdeApostada > 10)
            {
                gotoxy(35, 20);
                printf("Quantidade de numeros invalida");
                gotoxy(35, 21);
                printf("Quantidade de numero apostado: ");
                scanf("%d", &QtdeApostada);
            }
            clrscr();
            Moldura(30,3,95,25);
            gotoxy(35, 4);
            printf("Quantidade cadastrada");
            CadApostas[TLAP].QtdeNumApostado = QtdeApostada;

            int j = 0, k = 0;
            gotoxy(35, 5);
            printf("Numeros apostados: ");
            while (j < QtdeApostada)
            {
                gotoxy(35, 6 + j);
                printf("Numero[1-60]: ");
                scanf("%d", &CadApostas[TLAP].NumApostado[j]);
                while (CadApostas[TLAP].NumApostado[j] < 1 || CadApostas[TLAP].NumApostado[j] > 60)
                {
                    gotoxy(35, 8 + j);
                    printf("Numero invalido!");
                    gotoxy(35, 10 + j);
                    printf("Numero[1-60]: ");
                    scanf("%d", &CadApostas[TLAP].NumApostado[j]);
                }
                k = 0;
                while (k < j)
                {
                    if (CadApostas[TLAP].NumApostado[j] == CadApostas[TLAP].NumApostado[k])
                    {
                        gotoxy(35, 9 + j);
                        printf("Numero ja apostado!");
                        CadApostas[TLAP].NumApostado[j] = 0;
                    }
                    k++;
                }
                if (CadApostas[TLAP].NumApostado[j] == 0)
                {
                    gotoxy(35, 12 + j);
                    printf("Numero nao cadastrado!");
                }
                else
                {
                    NumeroMaisApostado[CadApostas[TLAP].NumApostado[j] - 1]++;
                    gotoxy(35, 12 + j);
                    printf("Numero cadastrado!");
                    j++;
                }
            }
            gotoxy(35, 12);
            printf("Sua aposta foi cadastrada!");
            TLAP++;
            getch();
            clrscr();
            Moldura(30, 3, 90, 25); 
            gotoxy(35, 10);
            printf("Deseja fazer outra aposta?");
            opc = toupper(getch());
            if (opc == 'S')
            {
                gotoxy(35, 12);
                printf("Numero da aposta para cadastro: ");
                scanf("%d", &NumAposta);    
                clrscr();
            }
            else
                NumAposta = 0;
        }
    }
}
void CONSApostas(TpApostas ConsApostas[TFAP], int TLAP,TpApostadores ConsCPF[TFA],int TLA,TpConc ConsConc[TFC],int TLC)
{
	int pos=0,NumConsAposta;
	clrscr();
	if(TLAP == 0)
	{
		printf("Nenhuma aposta cadastrada");
		getch();
	}
	else
	{
		printf("\nNumero da aposta para consulta: ");
		scanf("%d",&NumConsAposta);
		pos = BuscaAposta(ConsApostas,TLAP,NumConsAposta);
		while(pos == -1)
		{
			printf("\nNumero da aposta nao encontrado!");
			printf("\nNumero da aposta que deseja consultar: ");
			scanf("%d",&NumConsAposta);
			pos = BuscaAposta(ConsApostas,TLAP,NumConsAposta);
		}
		printf("\nNumero da aposta encontrado");
		printf("\nNumero da aposta: %d",ConsApostas[pos].NumAposta);
		printf("\nNumero do CPF: %s",ConsApostas[pos].CPFApostador);
		printf("\nNumero do concurso: %d",ConsApostas[pos].NmeroConc);
		printf("\nQuantidade de numero apostados: %d",ConsApostas[pos].QtdeNumApostado);
		int j=0;
		while (j < ConsApostas[pos].QtdeNumApostado)
		{
			printf("\n%do numero: %d",j+1,ConsApostas[pos].NumApostado[j]);
			j++;
		}
		getch();
			
	}
}
void ALTApostas(TpApostas AltApostas[TFAP], int TLAP)
{
	clrscr();
	char opc;
	int NumApostaAlt,pos;
	if(TLAP == 0)
	{
		printf("Nenhuma aposta cadastrada");
		getch();
	}
	else
	{
		printf("Numero da aposta: ");
		scanf("%d",&NumApostaAlt);
		pos = BuscaAposta(AltApostas,TLAP,NumApostaAlt);
		while(pos == -1)
		{
			printf("\nNumero da aposta nao encontrado!");
			printf("Numero da aposta: ");
			scanf("%d",&NumApostaAlt);
			pos = BuscaAposta(AltApostas,TLAP,NumApostaAlt);
		}
		printf("\nNumero da aposta encontrado!");
		printf("\nDeseja alterar  sua aposta? \n[S] - Sim\n[N] - Nao");
		opc = toupper(getche());
		if(opc == 'S')
		{
			printf("\nQuantidade de numeros que voce apostou: %d",AltApostas[pos].QtdeNumApostado);
			printf("\nQual a nova quantia de numeros que deseja apostar?: ");
			scanf("%d",&AltApostas[pos].QtdeNumApostado);
			while(AltApostas[pos].QtdeNumApostado <5 || AltApostas[pos].QtdeNumApostado>10)
			{
				printf("\nQuantidade de numeros invalida");
				printf("\nQuantidade de numero apostado: ");
				scanf("%d",&AltApostas[pos].QtdeNumApostado);
			}
			printf("\nQuantidade cadastrada");
			int j=0,k=0;
			printf("\n\nNumeros apostados: ");
			while(j < AltApostas[pos].QtdeNumApostado)
			{
				
				printf("\nNumero[1-60]: ");
				scanf("%d",&AltApostas[pos].NumApostado[j]);
				while(AltApostas[pos].NumApostado[j] <1 || AltApostas[pos].NumApostado[j] >60)
				{
					printf("\nNumero invalido!");
					printf("\nNumero[1-60]: ");
					scanf("%d",&AltApostas[pos].NumApostado[j]);
				}
				k=0;
				while(k <j)
				{
					if(AltApostas[pos].NumApostado[k] == AltApostas[pos].NumApostado[j])
					{
						printf("\nNumero ja apostado!");
						AltApostas[pos].NumApostado[j] = 0;
					}
					k++;
				}
				if(AltApostas[pos].NumApostado[j] == 0)
					printf("\nNumero nao cadastrado!");
				else
				{
					printf("\n Numero cadastrado!");
					j++;
				}
			}
			printf("\nAlteracao feita!");
			getch();
		}
		else
		{
			printf("\nAlteracao cancelada!");
			getch();
		}
		
	}
}
void EXCLApostas(TpApostas ExclApostas[TFAP], int &TLAP)
{
	clrscr();
	char opc;
	int i,pos,ExclAposta;
	if(TLAP == 0)
	{
		printf("Nenhuma aposta cadastrada!");
		getch();
	}
	else
	{
		printf("Numero da aposta que deseja excluir: ");
		scanf("%d",&ExclAposta);
		pos = BuscaAposta(ExclApostas,TLAP,ExclAposta);
		while(pos == -1)
		{
			printf("\nAposta nao encontrada!");
			printf("Numero da aposta que deseja excluir: ");
			scanf("%d",&ExclAposta);
			pos = BuscaAposta(ExclApostas,TLAP,ExclAposta);
		}
		printf("\nAposta encontrada");
		printf("\nCPF: %s",ExclApostas[pos].CPFApostador);
		printf("\nNumero do concurso: %d",ExclApostas[pos].NmeroConc);
		printf("\nNumero da aposta: %d",ExclApostas[pos].NumAposta);
		printf("\nQuantidade de numeros apostados: %d",ExclApostas[pos].QtdeNumApostado);
		for(i =0;i <ExclApostas[pos].QtdeNumApostado;i++)
			printf("\n%do Numero: %d",i+1,ExclApostas[pos].NumApostado[i]);
		printf("\nDeseja mesmo excluir sua aposta? \n[S] - Sim\n[N] - Nao");
		opc = toupper(getch());
		if(opc == 'S')
		{
			for(i=pos;i < TLAP-1;i++)
			{
				strcpy(ExclApostas[i].CPFApostador,ExclApostas[i+1].CPFApostador);
				ExclApostas[i].NmeroConc = ExclApostas[i+1].NmeroConc;
				ExclApostas[i].NumAposta = ExclApostas[i+1].NumAposta;
				ExclApostas[i].QtdeNumApostado = ExclApostas[i+1].QtdeNumApostado;
				for(int j=0;j< ExclApostas[i].QtdeNumApostado; j++)
					ExclApostas[i].NumApostado[j] = ExclApostas[i+1].NumApostado[j];
			}
			TLAP--;
			printf("\nExclusao concluida!");
			printf("%d",TLAP);
			getch();
		}
		else
		{
			printf("\nExclusao nao concluida!");
			getch();
		}
	}
}
void ResultadoConcurso(TpConc Resultados[TFC],int TLC)
{
	clrscr();
	int pos,i=0,NumConc;
	printf("\nNumero do concurso: ");
	scanf("%d",&NumConc);
	pos = BuscaConcurso(Resultados,TLC,NumConc);
	while(pos == -1)
	{
		printf("\nConcurso nao encontrado!");
		printf("\nNumero do concurso: ");
		scanf("%d",&NumConc);
		pos = BuscaConcurso(Resultados,TLC,NumConc);
	}
	printf("\nConcurso encontrado");
	while(i < 5)
	{
		printf("\n%do Numero: %d",i+1,Resultados[pos].NumSort[i]);
		i++;	
	}
	getch();
}
void ValidacaoApostas(Terno Tres[TFAP],int &QtdeTerno,Quadra Quatro[TFAP],int &QtdeQuadra,Quina Cinco[TFAP],int &QtdeQuina,TpConc ValidacaoConc[TFC],int TLC,TpApostas ValidacaoAposta[TFAP],int TLAP)
{
	clrscr();
	int i = 0, j, k, QtdeAcertos;
	while (i < TLAP) 
	{
	    QtdeAcertos = 0; // zera os acertos para essa aposta
	    j = 0;
	    // procura qual concurso foi sorteado para essa aposta
	    int idxConcurso = -1;
	    for (int c = 0; c < TLC; c++) 
		{
	        if (ValidacaoConc[c].NumConc == ValidacaoAposta[i].NmeroConc)
			{
	            idxConcurso = c;
	            break;
	        }
	    }
	    if (idxConcurso != -1) 
		{
	        while (j < ValidacaoAposta[i].QtdeNumApostado) 
			{
	            k = 0;
	            while (k < 5) 
				{ // 5 números sorteados
	                if (ValidacaoAposta[i].NumApostado[j] == ValidacaoConc[idxConcurso].NumSort[k]) 
					{
	                    QtdeAcertos++;
	                    break; // evita contar o mesmo número mais de uma vez
	                }
	                k++;
	            }
	            j++;
	        }
	        // Aqui você verifica se foi terno, quadra ou quina e salva:
	        if (QtdeAcertos == 3) 
			{
	         	Tres[QtdeTerno].ApostaTerno = ValidacaoAposta[i].NumAposta;
				Tres[QtdeTerno].ConcursoTerno = ValidacaoAposta[i].NmeroConc;
				QtdeTerno++;   
	        } else if (QtdeAcertos == 4) 
			{
				Quatro[QtdeQuadra].ApostaQuadra = ValidacaoAposta[i].NumAposta;
				Quatro[QtdeQuadra].ConcursoQuadra = ValidacaoAposta[i].NmeroConc;
				QtdeQuadra++;
	        } else if (QtdeAcertos == 5) 
			{
	            Cinco[QtdeQuina].ApostaQuina = ValidacaoAposta[i].NumAposta;
				Cinco[QtdeQuina].ConcursoQuina = ValidacaoAposta[i].NmeroConc;
				QtdeQuina++;
	        }
	    }

    i++;
	}
	printf("\nValidacao das apostas feitas!");
	getch();
}	

void VerificacaoApostas(TpApostas VerificacaoAposta[TFAP], int &TLAP,TpConc VerificacaoConc[TFC],int TLC,TpApostadores VerificacaoApostador[TFA], int TLA)
{
	clrscr();
	int posConc,pos,NumAposta,QtdadeAcertos=0,NumAcertados[5],i=0,j=0,NumConc=0;
	if(TLAP == 0)
	{
		printf("Nenhuma aposta cadastrada!");
		getch();
	}
	else
	{
		printf("Digite o numero da aposta que deseja fazer a verificacao: ");
		scanf("%d",&NumAposta);
		pos = BuscaAposta(VerificacaoAposta,TLAP,NumAposta);
		while(pos == -1)
		{
			printf("\nNumero da aposta nao encontrado!");
			printf("\nDigite o numero da aposta que deseja fazer a verificacao: ");
			scanf("%d",&NumAposta);
			pos = BuscaAposta(VerificacaoAposta,TLAP,NumAposta);
		}
		printf("\nNumero da aposta encontrado!");
		NumConc = VerificacaoAposta[pos].NmeroConc;
		posConc = BuscaConcurso(VerificacaoConc,TLC,NumConc);
		while(i < VerificacaoAposta[pos].QtdeNumApostado)
		{
			j=0;
			while(j < 5)
			{
				if(VerificacaoAposta[pos].NumApostado[i] == VerificacaoConc[posConc].NumSort[j])
				{
					NumAcertados[j] = VerificacaoAposta[pos].NumApostado[i];
					QtdadeAcertos++;
				}
				j++;
			}
			i++;
		}
		printf("\nNumero do concurso: %d",NumConc);
		printf("\nNumero da aposta: %d",NumAposta);
		printf("\nQuantidade de dezenas apostadas: %d",VerificacaoAposta[pos].QtdeNumApostado);
		i=0;
		while(i < VerificacaoAposta[pos].QtdeNumApostado)
		{
			printf("\n%do Numero: %d",i+1,VerificacaoAposta[pos].NumApostado[i]);
			i++;
		}
		i=0;
		if(QtdadeAcertos == 3)
		{
			printf("\nVoce fez um terno!");
			while(i < QtdadeAcertos)
			{
				printf("\n%do Numero Acertado: %d",i+1,NumAcertados[i]);
				i++;
			}
			
		}
		if(QtdadeAcertos == 4)
		{
			printf("\nVoce fez uma quadra!");
			while(i < QtdadeAcertos)
			{
				printf("\n%do Numero Acertado: %d",i+1,NumAcertados[i]);
				i++;
			}		
		}
		if(QtdadeAcertos == 5)
		{
			printf("\nVoce fez uma quina!");
			while(i < QtdadeAcertos)
			{
				printf("\n%do Numero Acertado: %d",i+1,NumAcertados[i]);
				i++;
			}
		}
		if(QtdadeAcertos == 2)
		{
			printf("\nVoce acertou apenas dois numeros!");
			while(i < QtdadeAcertos)
			{
				printf("\n%do Numero Acertado: %d",i+1,NumAcertados[i]);
				i++;
			}
		}
		if(QtdadeAcertos == 1)
		{
			printf("\nVoce acertou apenas um numero!");
			while(i < QtdadeAcertos)
				printf("\n%do Numero Acertado: %d",i+1,NumAcertados[i]);
		}
		if(QtdadeAcertos == 0)
			printf("\nVoce nao acertou nenhum numero!");
		getch();
	}
	
}
void MaisSorteado(int NumMaisSorteado[60],int TLC)
{
	int i=0,j=0;
	Sorteado CopiaMaisSorteado[60],AuxNum;
	system("cls");
	if(TLC == 0)
	{
		printf("Nenhum concurso cadastrado!");
		getch();
	}
	else
	{
			for(i=0;i<60;i++)
		{
			CopiaMaisSorteado[i].Num = i+1;
			CopiaMaisSorteado[i].Quantidade = NumMaisSorteado[i];
		}
		for(i=0;i<60-1;i++)
			for(j=0;j<60-1-i;j++)
				if(CopiaMaisSorteado[j].Quantidade < CopiaMaisSorteado[j+1].Quantidade)
				{
					AuxNum = CopiaMaisSorteado[j];
					CopiaMaisSorteado[j] = CopiaMaisSorteado[j+1];
					CopiaMaisSorteado[j+1] = AuxNum;
				}
		for(i=0;i<5;i++)
			printf("\nNumero %d (Sorteado %d vezes)",CopiaMaisSorteado[i].Num,CopiaMaisSorteado[i].Quantidade);
		getch();
	}
}
void MenosSorteados(int NumMaisSorteado[60],int TLC)
{
	int i=0,j=0,pos=0;
	system("cls");
	Sorteado MenosSorteado[60],AuxNum;
	if(TLC == 0)
	{
		printf("Nenhum concurso cadastrado!");
		getch();
	}
	else
	{
		for(i=0;i<60;i++)
		{
			MenosSorteado[i].Num = i+1;
			MenosSorteado[i].Quantidade = NumMaisSorteado[i];
		}
		for(i=0;i<60-1;i++)
			for(j=0;j<60-1-i;j++)
				if(MenosSorteado[j].Quantidade > MenosSorteado[j+1].Quantidade)
				{
					AuxNum = MenosSorteado[j];
					MenosSorteado[j] = MenosSorteado[j+1];
					MenosSorteado[j+1] = AuxNum;
				}
		for(i=0;i<60;i++)
			if(MenosSorteado[i].Quantidade == 0)
				pos++;
		for(i=pos;i<(pos+5);i++)
			printf("\nNumero %d (Sorteado %d vezes)",MenosSorteado[i].Num,MenosSorteado[i].Quantidade);
		getch();
	}
	
}
void MaisApostado(int NumMaisApostado[60],int TLAP)
{
	int i=0,j;
	Apostado CopiaMaisApostado[60],AuxNum;
	system("cls");
	if(TLAP == 0)
	{
		printf("Nenhuma aposta foi cadastrada");
		getch();
	}
	else
	{
			for(i = 0; i < 60; i++) 
		{
			CopiaMaisApostado[i].Num = i+1;
	        CopiaMaisApostado[i].Quantidade = NumMaisApostado[i];
	    }
	    for (i = 0; i < 60 - 1; i++) 
	        for (j = 0; j < 60 - 1 - i; j++) 
	            if (CopiaMaisApostado[j].Quantidade < CopiaMaisApostado[j + 1].Quantidade) 
				{
	                AuxNum = CopiaMaisApostado[j];
	                CopiaMaisApostado[j] = CopiaMaisApostado[j + 1];
	                CopiaMaisApostado[j + 1] = AuxNum;
	            }
	    for (i = 0; i < 5; i++) 
	        printf("Numero %d (Apostado %d vezes)\n", CopiaMaisApostado[i].Num, CopiaMaisApostado[i].Quantidade);
	    getch();
	}
	
}
void MenosApostado(int NumMenosApostado[60],int TLAP)
{
	int i=0,j=0,pos=0;
	Apostado CopiaMenosApostado[60],AuxNum;
	system("cls");
	if(TLAP == 0)
	{
		printf("Nenhuma aposta foi cadastrada!");
		getch();
	}
	else
	{
				for(i;i<60;i++)
		{
			CopiaMenosApostado[i].Num = i+1;
			CopiaMenosApostado[i].Quantidade = NumMenosApostado[i];
		}
		for(i=0;i<60-1;i++)
			for(j=0;j<60-1-i;j++)
				if(CopiaMenosApostado[j].Quantidade > CopiaMenosApostado[j + 1].Quantidade)
				{
					AuxNum=CopiaMenosApostado[j];
					CopiaMenosApostado[j]=CopiaMenosApostado[j+1];
					CopiaMenosApostado[j+1] = AuxNum;
				}
		for(i=0;i<60;i++)
			if(CopiaMenosApostado[i].Quantidade == 0)
				pos++;
		for(i=pos;i<(pos+5);i++)
			printf("Numero %d (Apostado %d vezes)\n",CopiaMenosApostado[i].Num,CopiaMenosApostado[i].Quantidade);
		getch();
	}
}

void NumMaisApostadoConc(Terno ternos[TFAP],int TLTerno,Quadra quadras[TFAP],int TLQuadra,Quina quinas[TFAP],int TLQuina,TpApostadores NumCpf[TFA],int TLA,TpApostas NumAposta[TFAP],int TLAP,TpConc NumConc[TFC],int TLC)
{
	clrscr();
	int Sorteado,NumeroConc,Numero,pos,i;
	printf("[3] - Terno\n [4] - Quadra\n[5] - Quina");
	scanf("%d",&Sorteado);
	printf("\nEm qual concurso procurar?: ");
	scanf("%d",&NumeroConc);
	pos = BuscaConcurso(NumConc,TLC,NumeroConc);
	while(pos == -1)
	{
		printf("\nNumero de concurso nao encontrado");
		printf("\nDigite outro numero: ");
		scanf("%d",&NumeroConc);
		pos = BuscaConcurso(NumConc,TLC,NumeroConc);
	}
	printf("\nConcurso encontrado!");
	switch(Sorteado)
	{
		case 3:
			printf("\n--- Apostas com Terno no concurso %d ---\n", NumeroConc);
			for (i = 0; i < TLTerno; i++) 
				if (ternos[i].ConcursoTerno == NumeroConc) 
					printf("Aposta: %d\n", ternos[i].ApostaTerno);
			break;
		case 4:
			printf("\n--- Apostas com Quadra no concurso %d ---\n", NumeroConc);
			for (i = 0; i < TLQuadra; i++) 
				if (quadras[i].ConcursoQuadra == NumeroConc) 
					printf("Aposta: %d\n", quadras[i].ApostaQuadra);
			break;
		case 5:
			printf("\n--- Apostas com Quina no concurso %d ---\n", NumeroConc);
			for (i = 0; i < TLQuina; i++) 
				if (quinas[i].ConcursoQuina == NumeroConc) 
					printf("Aposta: %d\n", quinas[i].ApostaQuina);
			break;
	}
	getch();
}
void RelatorioPremiados(Terno ganhadoresTerno[], int TLTerno,Quadra ganhadoresQuadra[], int TLQuadra, Quina ganhadoresQuina[], int TLQuina,int TLAP)
{
    int i;
    clrscr();
    if(TLAP == 0)
    {
    	printf("Nenhuma aposta cadastrada!");
    	getch();
    }
    else
    {
	    	 printf("===== RELATÓRIO DE APOSTAS PREMIADAS =====\n");
	
	    // Terno
	    printf("\n--- Terno (3 acertos) ---\n");
	    if (TLTerno == 0)
	        printf("Nenhuma aposta acertou um terno.\n");
	    else
	        for (i = 0; i < TLTerno; i++) 
	            printf("Concurso: %d | Aposta: %d\n",ganhadoresTerno[i].ConcursoTerno,ganhadoresTerno[i].ApostaTerno);
	    // Quadra
	    printf("\n--- Quadra (4 acertos) ---\n");
	    if (TLQuadra == 0)
	        printf("Nenhuma aposta acertou uma quadra.\n");
	    else 
	        for (i = 0; i < TLQuadra; i++) 
	            printf("Concurso: %d | Aposta: %d\n",ganhadoresQuadra[i].ConcursoQuadra,ganhadoresQuadra[i].ApostaQuadra);
	    // Quina
	    printf("\n--- Quina (5 acertos) ---\n");
	    if (TLQuina == 0)
	        printf("Nenhuma aposta acertou uma quina.\n");
	    else 
	        for (i = 0; i < TLQuina; i++) 
	            printf("Concurso: %d | Aposta: %d\n",ganhadoresQuina[i].ConcursoQuina,ganhadoresQuina[i].ApostaQuina);
	    // Totais
	    printf("\n===== TOTAL DE GANHADORES =====\n");
	    printf("Terno: %d\n", TLTerno);
	    printf("Quadra: %d\n", TLQuadra);
	    printf("Quina: %d\n", TLQuina);
    	getch();
	}
}
void ResumoPremiados(TpApostas CadApostas[TFAP], int TLAP, TpConc CadConcurso[TFC], int TLC, Terno Ternos[TFAP], Quadra Quadras[TFAP], Quina Quinas[TFAP]) 
{
    int i, j;
    clrscr();
    ConcursoPremiado Resumo[TFC];
    if(TLAP == 0)
    {
    	printf("Nehnuma aposta cadastrada!");
    	getch();
    }
    else
    {
	    for (i = 0; i < TLC; i++) 
		{
	        Resumo[i].ConcursoNum = CadConcurso[i].NumConc;
	        Resumo[i].QtdeApostadoresPremiados = 0;
	    }
	    for (i = 0; i < TLAP; i++) 
	        for (j = 0; j < TLC; j++) 
	            if (CadApostas[i].NmeroConc == CadConcurso[j].NumConc) 
				{
	                // Verificando Terno (3 acertos)
	                if (VerificaTerno(CadApostas[i], CadConcurso[j])) 
	                    Resumo[j].QtdeApostadoresPremiados++;
	                // Verificando Quadra (4 acertos)
	                else if (VerificaQuadra(CadApostas[i], CadConcurso[j])) 
	                    Resumo[j].QtdeApostadoresPremiados++;
	                // Verificando Quina (5 acertos)
	                else if (VerificaQuina(CadApostas[i], CadConcurso[j]))
	                    Resumo[j].QtdeApostadoresPremiados++;
	            }
	    // Ordenando o array Resumo por QtdeApostadoresPremiados em ordem decrescente
	    for (i = 0; i < TLC - 1; i++) 
	        for (j = 0; j < TLC - 1 - i; j++) 
	            if (Resumo[j].QtdeApostadoresPremiados < Resumo[j + 1].QtdeApostadoresPremiados) 
				{
	                // Troca de posições
	                ConcursoPremiado temp = Resumo[j];
	                Resumo[j] = Resumo[j + 1];
	                Resumo[j + 1] = temp;
	            
	    		}
	    // Exibindo o resumo
	    printf("\nResumo de Apostadores Premiados em Cada Concurso:\n");
	    for (i = 0; i < TLC; i++) 
	        printf("\nConcurso %d: %d apostadores premiados", Resumo[i].ConcursoNum, Resumo[i].QtdeApostadoresPremiados);
	    getch();
    }
}

int main(void)
{
	Moldura(30,5,90,20);
	gotoxy(48,10);
	printf("FELLYPE LUZ E SILVA");
	gotoxy(48,12);
	printf("FABIO EDUARDO ALI DOS SANTOS");
	gotoxy(48,14);
	printf("KAIKE CHAVES DA SILVA");
	getch();
	TpConc Concurso[TFC];
	TpApostadores Apostadores[TFA];
	TpApostas Apostas[TFAP];
	Terno	GanhadoresTerno[TFAP];
	Quadra GanhadoresQuadra[TFAP];
	Quina GanhadoresQuina[TFAP];
	int TLTerno=0,TLQuadra=0,TLQuina=0;
	int TLC=0,TLA=0,TLAP=0,NumeroMaisApostado[60]={0},NumeroMaisSorteado[60]={0};
	char opc,opcao;
	do
	{
		clrscr();
		opc = Menu();
		switch(opc)
		{
			case 'A':
				opcao = MenuConcurso();
				switch(opcao)
				{
					case 'A':
						CADConcurso(Concurso,TLC,NumeroMaisSorteado);
						break;
					case 'B':
						CONSConcurso(Concurso,TLC);
						break;
					case 'C':
						ALTConcurso(Concurso,TLC);
						break;
					case 'D':
						EXCLConcurso(Concurso,TLC,Apostas,TLAP);
						break;
				}
				break;
			case 'B':
				opcao = MenuApostador();
				switch(opcao)
				{
					case 'A':
						CADApostadores(Apostadores,TLA);
						break;
					case 'B':
						CONSApostadores(Apostadores,TLA);
						break;
					case 'C':
						ALTApostadores(Apostadores,TLA);
						break;
					case 'D':
						EXCLApostadores(Apostadores,TLA);
						break;
					case 46:
						LISApostadores(Apostadores,TLA);
						break;
				
				}
				break;
			case 'C':
				opcao = MenuAposta();
				switch(opcao)
				{
					case 'A':
						CADApostas(Apostas,TLAP,Concurso,TLC,Apostadores,TLA,NumeroMaisApostado);
						break;
					case 'B':
						CONSApostas(Apostas,TLAP,Apostadores,TLA,Concurso,TLC);
						break;
					case 'C':
						ALTApostas(Apostas,TLAP);
						break;
					case 'D':
						EXCLApostas(Apostas,TLAP);
						break;
				}
				break;
			case 'D':
				VerificacaoApostas(Apostas,TLAP,Concurso,TLC,Apostadores,TLA);
				break;
			case 'E':
				RelatorioPremiados(GanhadoresTerno,TLTerno,GanhadoresQuadra,TLQuadra,GanhadoresQuina,TLQuina,TLAP);
				break;
			case 'F':
				ResumoPremiados(Apostas,TLAP,Concurso,TLC,GanhadoresTerno,GanhadoresQuadra,GanhadoresQuina);
				break;
			case 'G':
				MaisSorteado(NumeroMaisSorteado,TLC);
				break;
			case'H':
				MenosSorteados(NumeroMaisSorteado,TLC);
				break;
			case 'I':
				MaisApostado(NumeroMaisApostado,TLAP);
				break;
			case 'J':
				MenosApostado(NumeroMaisApostado,TLAP);
				break;	
			case 'K':
				ValidacaoApostas(GanhadoresTerno,TLTerno,GanhadoresQuadra,TLQuadra,GanhadoresQuina,TLQuina,Concurso,TLC,Apostas,TLAP);
				break;
			case 'L':
				NumMaisApostadoConc(GanhadoresTerno,TLTerno,GanhadoresQuadra,TLQuadra,GanhadoresQuina,TLQuina,Apostadores,TLA,Apostas,TLAP,Concurso,TLC);		
				break;
			case'Z':
				ResultadoConcurso(Concurso,TLC);
				break;
			
		}
	}while(opc!=27);
	
}
