#include<stdio.h>
#include<X11/Xlib.h>
#include<X11/keysym.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<errno.h>

#define PORT_NUMBER 9091

int main()
{
    // socket
    struct sockaddr_in cliaddr, servaddr; // socket structure
    int listenfd, connfd;
    pid_t clipid;

    if ( (listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0 )
    {
        perror("socket");
        exit(1);
    }
    memset( &servaddr, 0, sizeof(servaddr) ); // set serveraddr to zero
    servaddr.sin_family = AF_INET; // internet socket
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // any host address
    servaddr.sin_port = htons(PORT_NUMBER); // port

    if ( bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind");
        exit(1);
    }
    
    if ( listen(listenfd, 10) < 0 ) // listen with wait queue of 10
    {
        perror("listen");
        exit(1);
    }

    socklen_t clilen = sizeof(cliaddr);
    /*  accept blocks till we have new client connection*/
    connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen); 

    // X11 part    
    Display *display = NULL;
    unsigned int keycode;

    display = XOpenDisplay(NULL);
    keycode = XKeysymToKeycode(display, XK_Up);

    int left=0, right=0, up=0, down=0;

    while (1)
    {
    
        char c;
        read(connfd, &c, 1);
        if (c == 1)
        {
            if (left == 0)
            {
                // release other
                if (right == 1)
                {
                    keycode = XKeysymToKeycode(display, XK_Right);
                    printf ("Right Released\n");
                    XTestFakeKeyEvent(display, keycode, False, CurrentTime);
                    right = 0;
                }
                // press current
                keycode = XKeysymToKeycode(display, XK_Left);
                printf ("Left Pressed\n");
                XTestFakeKeyEvent(display, keycode, True, CurrentTime);
                XFlush(display);
                // set left
                left = 1;
            }
        }
        else if (c == 2)
        {
            if (right == 0)
            {
                // release other
                if (left == 1)
                {
                    keycode = XKeysymToKeycode(display, XK_Left);
                    printf ("Left Released\n");
                    XTestFakeKeyEvent(display, keycode, False, CurrentTime);
                    left = 0;
                }
                // Press current
                keycode = XKeysymToKeycode(display, XK_Right);
                printf ("Right Pressed\n");
                XTestFakeKeyEvent(display, keycode, True, CurrentTime);
                XFlush(display);
                //set right
                right = 1;
            }

        }        
        else if (c == 3)
        {
            if (left == 1)
            {
                keycode = XKeysymToKeycode(display, XK_Left);
                printf ("Left Released\n");
                XTestFakeKeyEvent(display, keycode, False, CurrentTime);
                left = 0;
            }
            if (right == 1)
            {
                keycode = XKeysymToKeycode(display, XK_Right);
                printf ("Right Released\n");
                XTestFakeKeyEvent(display, keycode, False, CurrentTime);
                right = 0;
            }
            XFlush(display);
        }

        else if (c == 4)
        {
            if (down == 0)
            {
                // release other
                if (up == 1)
                {
                    keycode = XKeysymToKeycode(display, XK_Up);
                    printf ("Up Released\n");
                    XTestFakeKeyEvent(display, keycode, False, CurrentTime);
                    up = 0;
                }
                // press current
                keycode = XKeysymToKeycode(display, XK_Down);
                printf ("Down Pressed\n");
                XTestFakeKeyEvent(display, keycode, True, CurrentTime);
                XFlush(display);
                // set left
                down = 1;
            }
        }
        else if (c == 5)
        {
            if (up == 0)
            {
                // release other
                if (down == 1)
                {
                    keycode = XKeysymToKeycode(display, XK_Down);
                    printf ("Down Released\n");
                    XTestFakeKeyEvent(display, keycode, False, CurrentTime);
                    down = 0;
                }
                // Press current
                keycode = XKeysymToKeycode(display, XK_Up);
                printf ("Up Pressed\n");
                XTestFakeKeyEvent(display, keycode, True, CurrentTime);
                XFlush(display);
                //set right
                up = 1;
            }

        }        
        else if (c == 6)
        {
            if (up == 1)
            {
                keycode = XKeysymToKeycode(display, XK_Up);
                printf ("Up Released\n");
                XTestFakeKeyEvent(display, keycode, False, CurrentTime);
                up = 0;
            }
            if (down == 1)
            {
                keycode = XKeysymToKeycode(display, XK_Down);
                printf ("Down Released\n");
                XTestFakeKeyEvent(display, keycode, False, CurrentTime);
                down = 0;
            }
            XFlush(display);
        }
    }

    return 0;
}
