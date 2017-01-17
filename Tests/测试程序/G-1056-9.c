const int max_len = 32;
int list[32];



int getn(int x){
  int tmp;
  tmp = 1;
  if(x <= 0){
    return (0);
  }
  if(x >= 1){
    return (getn(x - 1) + tmp);
  }
  return (0);
}

void dag(){
   int i,x,y,z,c ;
   x = 0 ;
   y = 0 ;
   z = 0 ;
   for(i = 0; i < getn(max_len)-3; i = i + 3 ){
     x = x + list[i] ;
     y = y + list[i+1] ;
     z = z + list[i+2] ;
   }

   c = 3 ;
   for(i = 0 ; i< 100; i = i +1){
     y = x * c + z - (y * 2) ;
     z = x * c - z + (y * 2) ;
     x = x * c + z - (y * 2) ;  
   }


   printf("x= ", x) ;
   printf("y= ", y) ;
   printf("z= ", z) ;

}
void quicksort(int i,int j)
{
        int x,y,z;
        int tmp;
        x = i;
        y = j;
        z = list[(x + y) / 2];
        do {
                do{
                        if( z > list[y]){
                                y = y - 1;
                        }
                } while ( z > list[y])

                do{
                        if( z < list[x]){
                                x = x + 1;
                        }
                } while ( z < list[x])

                if (x <= y){
                         tmp = list[x];
                         list[x] = list[y];
                         list[y] = tmp;
                         x = x + 1;
                         y = y - 1;
                }
        } while ( x <= y )
        if ( x < j) quicksort(x , j);
        if ( i < y) quicksort(i , y);
}

void print_list(int n)
{
   int i;
   for(i = 0; i < n ; i = i + 1){
      if( i == 1 ){
         printf(" ", list[i]);
      }
      if( i == 7){
         printf(" ", list[i]);
      }
      if( i == 12 ){
         printf(" ", list[i]);
      }
  }
}

void main()
{
   int i;

   for(i = 0; i < getn(max_len); i = i + 2 ){
     list[i] = i * 99 ;
   }

   for(i = getn(max_len-1); i >= 0; i = i - 2 ){
     list[i] = (max_len - i) * 99 ;
   }

   printf("before: ");
   print_list(max_len);

   quicksort(0,max_len - 1);

   printf(" after: ");
   print_list(max_len);

   dag() ;

   return;
}
