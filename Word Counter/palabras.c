/*	
 * Luis Ramos
 * luuisraam@gmail.com
 * Estudiante de Matemáticas Aplicadas y Computación, UNAM
 * 2019
 * 
 *
 * 
 * 
 * LEEME!!
 * 
 * General: 
 *      Este programa lee un archivo de texto, identifica cada palabra existente y las guarda en una
 *      estructura, cuenta la frecuencia de cada palabra, y a travéz de Bubble Sort ordena la estruc
 *      tura de mayor a menor aparición. Al final imprime en un archivo cada palabra con su frecuen-
 *      cia de mayor a menor.
 * 	
 * Considreaciones: 
 * 1)	El usuario deberá ingresar el nombre del archivo de texto completo,  es decir,  junto con su
 *      extensión.
 * 			
 *      Ejemplo: MiArchivoDeTexto.txt ó MiArchivoDeTexto.dat
 * 
 * 2)	Tanto el archivo de texto a leer como el ejecutable de este programa deben encontrarse en la
 *      misma carpeta raíz, de caso contrario el programa no lo encontrará.
 * 
 * 3)   El resultado será emitido en otro archivo llamado "nube.txt".
 * 
 * 4)   El programa si hace diferencia entre  mayúsucalas y  minúsculas eso significa que "School" y
 *      "school", son palabras diferentes.
 * 
 * 5)  	Se emitirán dos totales de palabras, uno tomando en cuenta cada palabra existente (con repe-
 *      ticion), y otro totalizando (sin repetición).    Se cumple que (sin repetición <= con repeti
 *      ción)
 * 
 * 6)	Solo utilizarlo con texto en inglés,    en las siguientes versiones se ampliará el soporte a
 *      las palabras en español que cuentan con acentos.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAT_MAX 2000

typedef struct mat
    {
        char palabra[40];
        int frec;
    } 	matriz;
	
	
/*----------------------------------------------------------------------
 * Recibe el nombre del archivo y el modo de apertura, retorna el punte-
 * ro al archivo.
 ---------------------------------------------------------------------*/
FILE * apertura (char * nombre_archivo, char * modo)
{
    FILE * archivo = fopen ( nombre_archivo, modo);
    if ( archivo == NULL )
        printf ("\n\t [x] No se pudo aperturar el archivo (%s): %s", 

    nombre_archivo, strerror(errno));

    return archivo;
}


int main ()
{
	
    char 		c, *auxiliar, nombre_archivo[25];
    int 		k = 0, i = 0, j = 0, aux;
    int 		cont = 0, cont2 = 0;

    matriz 		A[MAT_MAX];
/*--------------------------------------------------------------------*/

    printf ("\n\t\t* Contador de palabras *\n");	
    printf ("\n\tNota: el archivo debe de estar en la raiz del *.exe");
    printf ("\n\n\tIngresa el nombre del archivo con extension: ");
    scanf ("%s", nombre_archivo);

    FILE * archivo = apertura ( nombre_archivo, "r");
    rewind (archivo);

    /* Cadena que servira como auxiliar de lectura */
    auxiliar = (char *) malloc (40);


    i = 0; j = 0;
	
/*--------------------------------------------------------------------*/

    /* Se llena la estructura con todas las palabras del texto */
    if ( archivo != NULL )
        {	
        while ( ( c = fgetc (archivo) ) != EOF )
        {
            /* Valida que sean solo letras o apóstrofe y va llenando
             * el vector auxiliar para guardar la palabra completa */
            if ( isalpha (c) || c == 39 )
            {
                auxiliar[i] = c;
                i++;
            }
            /* Cuando el caracter sea un espacio o salto o tabulación
             * si i >= 1 entonces en auxiliar tenemos una palabra */ 
            else if( isspace (c) || c == '\n' || c == '\t')
            { 
                if ( i>=1 )
                {
                    auxiliar[i] = '\0';
                    strcpy (A[j].palabra, auxiliar);
                /* Se reinicia el indice de auxiliar para leer otra 
                 * palabra, y se aumenta el indice j de la estructura
                 * para guardar una nueva palabra */
                    i = 0; j++;
                }
            }
        } fclose (archivo);
    }

/*--------------------------------------------------------------------*/
	
    /* cont es la cantidad de palabras que se encontraron
     * tomando en cuenta la repeticion */
    cont = j;

    /* Se inicializa la frecuencia en uno ya que será sumada, debido a que se
     * supone que al menos cada palabra se encuentra una vez, de esta */
    for (i = 0; i < MAT_MAX; i++)
        A[i].frec = 1;
    /* Al encontrar una palabra igual entonces se eliminará de la es-
     * tructura y se aumentará la frecuencia */
    for (i = 0; i < cont-1; i++)
        for (j = i; j < cont-1; )
        {
            if (!strcmp (A[i].palabra, A[j+1].palabra))
            {
                A[i].frec++;
                /* Elimina las palabras identicas recorriendo el vector
                 * copiando la palabra j+1 a la j */ 
                for ( k = j+1; k < cont-1; k++ )
                    strcpy ( A[k].palabra, A[k+1].palabra);
                
                cont--;
            }
            else
                j++;
        }

    i=0; j=0;
	
/*--------------------------------------------------------------------*/

    /* Método burbuja para ordenar el vector de frecuencias */
    for ( i=0; i < cont; i++ )
    {
        for ( j=0; j < cont-i; j++)
        {
            if (A[j].frec < A[j+1].frec)
                {
                    /* El proceso es análogo, el intercambio se hace
                     * tanto frecuencia como en palabra */
                    aux = A[j].frec;
                    strcpy ( auxiliar, A[j].palabra);
                    A[j].frec = A[j+1].frec;
                    strcpy ( A[j].palabra, A[j+1].palabra);
                    A[j+1].frec = aux;
                    strcpy ( A[j+1].palabra, auxiliar);
                }	
        }
    }
	
/*--------------------------------------------------------------------*/
	
    /* Escritura en el archivo de respuesta */
    if ( archivo != NULL )
    {	

        FILE * archivo_res = apertura ( "nube.txt", "w");

        fprintf (archivo_res,"\n\n\t NOTA: ESTE PROGRAMA SI DIFERENCIA ENTRE MAYUSCULAS Y MINUSCULAS");
        fprintf (archivo_res,"\n\t       MOSTRARA LAS PALABRAS ENCONTRADAS");
        fprintf (archivo_res,"\n\n\n\t * Total de palabras sin contar repeticion: %d", cont);
        fprintf (archivo_res,"\n\n     N - \t PALABRA \t: FRECUENCIA\n");
        
        for ( i = 0; i < cont; i++ )
        {
            fprintf (archivo_res, "\n %5d -  %-20s \t:  %d", i+1, A[i].palabra, A[i].frec );
            cont2 = cont2 + A[i].frec;
        }
        
        fprintf (archivo_res,"\n\n\t * Total de palabras contando repeticion: %d\n", cont2);
        fclose (archivo_res);
        
        printf ("\n\t[!] El archivo nube.txt fue generado exitosamente.\n\n");
        
        /* Abre el archivo automaticamente, no es standard,
         *  solo en windows */
        // system ("start nube.txt");
        
    }
    /*--------------------------------------------------------------------*/

    free (auxiliar);

    return 0;
}
