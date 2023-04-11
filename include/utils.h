// convert string to lowercase
char *str_to_lower(char *str)
{
     for(char *ptr = str; *ptr != '\0'; ptr++)
     {
          *ptr = tolower(*ptr);
     }

     return str;
}

// get a size of a file
long int get_file_size(FILE *fptr)
{
     fseek(fptr, 0L, SEEK_END);
     long int size = ftell(fptr);
     return size;
}