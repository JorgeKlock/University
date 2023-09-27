Principal
{
    var
        entero n = 0;
	entero curr = 0; 
    varend

    salida("introduce numero "); 
    entrada("%d", &n); 
    salida("%d == ", n); 
    curr = 2; 
    mientras (curr <= n) 
    {
        var
        entero d = 1; 
        varend

	d = n/curr; 

        si ( d*curr == n )
        {
            salida("* %d ", curr); 
            n = n/curr; 
        }
        sino {
            curr = curr+1; 
	}
    } 
    salida("\n"); 
}
