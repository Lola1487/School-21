#include <stdio.h>
#include <stdlib.h>
#include <fcgi_stdio.h>

int main() {
    while (FCGI_Accept() >= 0) {
        printf("Content-type: text/html\r\n\r\n");
        printf("<html>\n");
        printf("<head>\n");
        printf("<title>Hello, World!</title>\n");
        printf("</head>\n");
        printf("<body>\n");
        printf("<h1>Hello, World!</h1>\n");
        printf("</body>\n");
        printf("</html>\n");
    }
    return 0;
}
