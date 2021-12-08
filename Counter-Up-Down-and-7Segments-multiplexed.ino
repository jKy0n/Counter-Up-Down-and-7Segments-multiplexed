// =====================================================================================================
// =====================================================================================================
// ===============================  Author:  John Kennedy Loria Segundo  ===============================
// ====================  Counter-Up-Down-and-7Segments-multiplexed.ino - ver.: 0.1  ====================
// =====================  Initial Date: ??/??/20?? - Last Modify Date: ??/??/2021  =====================
// =====================================================================================================
// =====================================================================================================
//
//
//
//
//
// STATUS:
//
//                      IN DEVELOPMENT
//
//
//
// Code Function:
//
//
//
//
//
// Simplify code description:
//
//
//
//
//
// Logical description:
//
//
//
//
//
//
// Version observations:
// 
//
//              This code was created only for educational proposes, as a code exercise 
//              in Arduino Lang for Arduino microcontroller (Arduino Uno).
//
//
//
//				This code use:
//
//				-		   Kit:		Arduino Uno
//				-			µC:		AVR (Atmel - )
//				-		 Clock:		?MHz (Xtal: ?MHz)
//				-		Editor:		VScode
//				-		Syntax:		Arduino Language
//				-    Libraries:		??
//				-	Compilator:		>> Not used yet <<
//				-	 Simulator:		SimulIDE
//
//
//
//									PROGRAM:
//  ----------------------------------------------------------------------------------------------------
//
//				Declarações Iniciais:

	#define 	C_UP	 11									// Define Pino 11 como "C_UP",
	#define 	C_DOWN	 10									// Define Pino 10 como "C_DOWN",
															// (Counter Up/Down)

	#define 	DOZENS	 9									// Define Pino 9 como "DOZENS",
	#define 	UNITS	 8									// Define Pino 8 como "UNITS",


		byte display[ 16 ] = 
		{ 
															//
		0x3F, 0x03, 0x6D, 0x67,								// Tabela com os 16 dígitos _
		0x53, 0x76, 0x7E, 0x23,								// de 0 à F (incluindo hexadecimais)
		0x7F, 0x77, 0x7B, 0x5E,								// para o display de 7 segmentos
		0x3C, 0x4F, 0x7C, 0x78 								// 

		};


	short	u	=	0 ;										// Cria a variável "u" (unidades),
	short	d	=	0 ;										// Cria a variável "d" (dezenas),

	short	SBU	=	0 ;										// Cria a variável "SBU",
	short	SBD	=	0 ;										// Cria a variável "SBD",
															// (State Button Up/Down)

// ----------------------------------------------------------------------------------------------------
//				Rotina Display:

	void Display()
	{		
		PORTD 	=	~(display[u]	<<	1 ) ;				// Ajusta o digito (unidade) e joga no PortD,
		digitalWrite( UNITS, HIGH ) ;						// Aciona segmentos das unidades,
		delay( 5 ) ;										// Aguarda 5 mili-segundos,
		digitalWrite( UNITS,  LOW ) ;						// Desaciona o segmentos da unidade,

		PORTD 	=	~(display[d]	<<	1 ) ;				// Ajusta o digito (dezena) e joga no PortD,
		digitalWrite( DOZENS, HIGH ) ;						// Aciona segmentos das dezenas,
		delay( 5 ) ;										// Aguarda 5 mili-segundos,
		digitalWrite( DOZENS,  LOW ) ;						// Desaciona o segmentos da dezena,
	}

// ----------------------------------------------------------------------------------------------------
//				Configurações iniciais:

	void setup()
	{

		for( int i = 1 ; i < 10 ; i++ )						// Resumindo:
		{
		    pinMode( i , OUTPUT ) ;							// Configura os pinos 1 a 9 como saída,
		}

		for( int j = 10 ; j < 12 ; j++ )
		{
		    pinMode( j , INPUT);							// Configura os pinos 10 e 11 como entrada,
		}													// (Sim, estou estudando o comando "for")
	}

// ----------------------------------------------------------------------------------------------------
//				Rotina Principal:

	void loop()
	{
		SBU	=	digitalRead( C_UP );						// Faz a leitura de C_UP e guarda em SBU,
		SBD	=	digitalRead( C_DOWN );						// Faz a leitura de C_DOWN e guarda em SBD,
		
		if( SBU != 1 )										// O botão C_UP foi pressionado?
		{
			if( u <= 0x09 )									// "u" (unidades) é menor ou igual que 9?
			++u ;											// Sim, incrementa "u" (unidades),

			if( u >= 0x0A )									// O dígito é maior ou igual a 10 (Ah)?
			{
			    u 	=	0 ;									// Sim, zera "u" (unidades),
			    ++d ;										// Incrementa "d" (dezenas),
			}
			
			delay( 150 ) ;									// Aguarda 150mS (deboucing)				
		}

		if( SBD != 1 )										// O botão C_DOWN foi pressionado?
		{
			if( u > 0x00 )									// "u" (unidades) é maior que 0?
			u = --u ;										// Sim, decrementa "u" (unidades)
			else											// Não...
			{
				if( u 	<=	0x00 )							// "u" (unidades) é menor ou igual a 0?
				{
					if( d > 0x00 )							// "d" (dezenas) é maior que 0?
					{
						u = 0x09 ;							// Sim, "u" (unidades) torna-se 9,
						--d ;								// Decrementa "d" (dezenas),
					}
				}
			}
			
			delay( 150 ) ;									// Aguarda 150mS (deboucing)
		}

		Display() ;											// Roda a sub-rotina Display
	}

// ----------------------------------------------------------------------------------------------------
//				FIM DO PROGRAMA! =)

