#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/io.h>
#include <string.h>
#include <math.h>

int stare_led[9];

void afisare(int led[10]) {
        int cit = inb(888);
        int x;
        for( x=0; x<8; x++ )
                if( led[x]!=1 )
                        cit &= ~(1<<x);
                else
                        cit |= 1<<x;
        outb(cit, 888);
        sleep(1);
}

int transformare(char sir[30]) {
        int i;
        int val=0;
        for(i=0;i<=strlen(sir);i++) {
                if(sir[i]>=48 && sir[i]<=57)
                        val=val*10+(int)(sir[i]-'0');
                if(sir[i]=='.') {
                        if(sir[i+1]-'0'>6)
                                val++;
                        i=strlen(sir)+1;
                }
        }
        return val;
}

void creare(int folosit, int total) {
        int i;
        for(i=0;i<=7;i++)
                if(i<(int)folosit/(total/8))
                        stare_led[i]=1;
                else
                        stare_led[i]=0;
}



int main() {
        unsigned char val;
        int x, z;
        int a=0;
        char used[30];
        if( ioperm(888,1,1) ) {
                printf("Couldn't get port 888\n");
                return 1;
        }
        FILE *fcpu;
        fcpu=popen("top -bn 2 -d 0.01 | grep '^%Cpu' | tail -n 1 | gawk '{print $2+$4+$6}'", "r");
        fgets(used, 30, fcpu);
        a=transformare(used);
        for(int z=0;z<=7;z++)
                if(z<(int)a/(100/8))
                        stare_led[z]=1;
                else
                        stare_led[z]=0;
        afisare(stare_led);
        outb(0,888);
        printf("%d\n", a);
        printf("%d\n", (int)a/(100/8));
        return 0;
        }
