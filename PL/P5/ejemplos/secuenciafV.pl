inicio
{
    inivar
        entero a, b, c;
    finvar;
    

    entero fib(entero input)
    {
        inivar
            entero retVal, aux1, aux2;
        finvar;        

        retVal = 0;
        
        si(input > 2)
        {
            aux1 = 0;
            aux2 = 1;
            para 2 hasta input aumentando
            {
                retVal = aux1 + aux2;
                aux1 = aux2;
                aux2 = retVal;

                anunciar("Fib: ", retVal, "\n");
            }
        }
        sino
        {
            si(input == 1)
            {
                retVal = 1;
            }
        }
  
        repatriar retVal;
    }


    anunciar("Ingresa un numero:\n>");

    escanear (b);

    a = fib(b);
}