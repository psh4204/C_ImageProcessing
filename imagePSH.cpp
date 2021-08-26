#define   _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
/* =======================================================================
   �̸� : �̴�������Ʈ_ImageProcessing
   ���� :1.0
   ���
   -�⺻���
     -���Ͽ���, ����, ����
   -����ó�����
    - ȭ����ó��, ������ó��, ȭ�ҿ���ó��, ������׷�ó��
   ======================================================================= */

   // ����������
#define UC unsigned char
HWND hwnd;  HDC hdc;
UC** m_InImage = NULL;     // Input_Image : �Է� �̹���(�̹����ʱⰪ)
UC** m_OutImage = NULL;     // Output_Image : ��� �̹���
int m_inH, m_inW, m_outH, m_outW; // �̹��� ����, �ʺ�
int menuInput = 0;
float version = 1.0; // ���� �Է�

// �Լ� ����� (����)
UC** malloc2D(int, int);    void free2D(UC**, int);
void openImage();           void saveImage();
void displayImage();

// �Լ� ����� (����ó��)
void equalImage();
void pmLightImage();        void mdLightImage();
void andCircleImage();      void orCircleImage();
void bwImage();             void bwAvgImage();
void ngtvImage();           void gammaImage();      void paraImage();

void zoomOutImage();        void zoomInImage();
void zoomInBackImage();
void mirrorLRImage();       void mirrorUDImage();
void moveImage();
void rotateImage();         void midRotateImage();  void midRotateFullImage();

void embossImage();
void blur3Image();          void blur5Image();      void blurImage();
void gausBlur3Image();      void sharp1Image();     void sharp2Image();
void hfSharpImage();

void vEdgeImage();          void hEdgeImage();
void  robertsVEdgeImage();  void robertsHEdgeImage();   void robertsEdgeImage();
void prwVEdgeImage();       void prwHEdgeImage();       void prwEdgeImage();
void  sobelVEdgeImage();    void sobelHEdgeImage();     void sobelEdgeImage();
void lapla4EdgeImage();     void laplam8EdgeImage();    void lapla8EdgeImage();
void logEdgeImage();        void dogEdgeImage();

void usaImage();            void minusImage();          void zoomInYSImage();       void rotateYSImage();

void histStretchImage();    void histEqualizeImage();   void histImage();

void printMenu() {
    int endPage = 4;
    if (menuInput > endPage) {
        menuInput = 0;
    }
    else if (menuInput < 0) {
        menuInput = endPage;
    }
    printf(" \n   ImageProcessing(Version %.1f)_�ڽ�ȯ\n", version);
    puts("-------------------------------------------------\n");
    puts("   [0.�̹�������] [1.����] [2.����] [3.����]\n");
    printf("---------------------[%d / %d]----------------------\n", menuInput, endPage);
    switch (menuInput) {
    case 0:
        puts("   [ȭ����ó��]\n");
        puts("(A.���)\t(B.������)\n");
        puts("(C.+-���)\t(D.*/���)\n");
        puts("(E.AND��)\t(F.OR��)\n");
        puts("(G.����)\t(H.����)\n");
        puts("(I.�Ķ󺼶�)\n");
        break;
    case 1:
        puts("   [������ó��]\n");
        puts("(A.���)\t(B.Ȯ��)\n");
        puts("(C.�����Ȯ��)\t(D.�̵�)\n");
        puts("(E.�¿�̷���)\t(F.���Ϲ̷���)\n");
        puts("(G.ȸ��)\t(H.�߾ӹ����ȸ��)\n");
        puts("\n[�缱��������]\n");
        puts("(I.ȸ��)\t(J.Ȯ��)\n");
        break;
    case 2:
        puts("   [ȭ�ҿ���ó��]\n");
        puts("(A.������)\n");
        puts("(B.3x3��)\t(C.5x5��)\n");
        puts("(D.�Է���պ�)\t(E.����þȺ�)\n");
        puts("(F.���������������1)\t(G.���������������2)\n");
        puts("(H.���������ͻ�����)\t\n");
        break;
    case 3:
        puts("   [ȭ�ҿ���ó��(����ó��)]\n");
        puts("(A.������)\t(B.��������)\n");
        puts("\n[1�� �̺� ȸ�� ����ũ]\n");
        puts("[�ι�������]\t(C.����) (D.����) (E.��������)\n");
        puts("[����������]\t(F.����) (G.����) (H.��������)\n");
        puts("[�Һ�����]]\t(I.����) (J.����) (K.��������)\n");
        puts("\n[2�� �̺� ȸ�� ����ũ]\n");
        puts("[���ö���]]\t(L.4)\t(M.-8)\t(N.8)\n");
        puts("(O.LOG����)\t(V.DoG����)\n");
        puts("\n[������]\n");
        puts("(Q.���翬����)\t(R.��������)\n");
        break;
    case 4:
        puts("   [������׷�ó��]\n");
        puts("(A.������׷�ǥ��)\n");
        puts("(B.��Ʈ��Ī)\t(C.��Ȱȭ)\n");
        break;
    }
    puts("-------------------------------------------------\n");
    puts(" >.���� �޴�\n");
    
}

// �����Լ�
int main() {
    hwnd = GetForegroundWindow();
    hdc = GetWindowDC(hwnd);

    char input = 0;
    while (true) {
        printMenu();
        input = _getch();
        if (menuInput == 0) {
            switch (input) {
            case '>': menuInput++; system("cls"); break;
            case '<': menuInput--; system("cls"); break;
            case '0': openImage(); break;
            case '1': saveImage(); break;
            case '2':equalImage(); break;
            case '3': free2D(m_InImage, m_inH); free2D(m_OutImage, m_outH); return 0;

            case 'a': case'A': bwImage(); break;
            case 'b': case'B': bwAvgImage(); break;
            case 'c': case'C': pmLightImage(); break;
            case 'd': case'D': mdLightImage(); break;
            case 'e': case'E': andCircleImage(); break;
            case 'f': case'F': orCircleImage(); break;
            case 'g': case'G': ngtvImage(); break;
            case 'h': case'H': gammaImage(); break;
            case 'i': case'I': paraImage(); break;

            default:
                if (input != 'x' && input != 'X') printf("-> �ùٸ� ���� �Է��ϼ���.\n"); break;
            }
        }
        else if (menuInput == 1) {
            switch (input) {
            case '>': menuInput++; system("cls"); break;
            case '<': menuInput--; system("cls"); break;
            case '0': openImage(); break;
            case '1': saveImage(); break;
            case '2':equalImage(); break;
            case '3': free2D(m_InImage, m_inH); free2D(m_OutImage, m_outH); return 0;

            case 'a': case'A': zoomOutImage();  break;
            case 'b': case'B': zoomInImage(); break;
            case 'c': case'C': zoomInBackImage(); break;
            case 'd': case'D': moveImage(); break;
            case 'e': case'E': mirrorLRImage(); break;
            case 'f': case'F': mirrorUDImage(); break;
            case 'g': case'G': rotateImage(); break;
            case 'h': case'H': midRotateFullImage(); break;
            case 'i': case'I': rotateYSImage(); break;
            case 'j': case'J': zoomInYSImage(); break;

            default:
                if (input != 'x' && input != 'X') printf("-> �ùٸ� ���� �Է��ϼ���.\n"); break;
            }
        }
        else if (menuInput == 2) {
            switch (input) {
            case '>': menuInput++; system("cls"); break;
            case '<': menuInput--; system("cls"); break;
            case '0': openImage(); break;
            case '1': saveImage(); break;
            case '2':equalImage(); break;
            case '3': free2D(m_InImage, m_inH); free2D(m_OutImage, m_outH); return 0;

            case 'a': case'A': embossImage(); break;
            case 'b': case'B': blur3Image(); break;
            case 'c': case'C': blur5Image(); break;
            case 'd': case'D': blurImage(); break;
            case 'e': case'E': gausBlur3Image(); break;
            case 'f': case'F': sharp1Image(); break;
            case 'g': case'G': sharp2Image(); break;
            case 'h': case'H': hfSharpImage(); break;

            default:
                if (input != 'x' && input != 'X') printf("-> �ùٸ� ���� �Է��ϼ���.\n"); break;
            }

        }
        else if (menuInput == 3) {
            switch (input) {
            case '>': menuInput++; system("cls"); break;
            case '<': menuInput--; system("cls"); break;
            case '0': openImage(); break;
            case '1': saveImage(); break;
            case '2':equalImage(); break;
            case '3': free2D(m_InImage, m_inH); free2D(m_OutImage, m_outH); return 0;

            case 'a': case'A': hEdgeImage(); break;
            case 'b': case'B': vEdgeImage(); break;
            case 'c': case'C': robertsVEdgeImage(); break;
            case 'd': case'D': robertsHEdgeImage(); break;
            case 'e': case'E': robertsEdgeImage(); break;
            case 'f': case'F': prwVEdgeImage(); break;
            case 'g': case'G': prwHEdgeImage(); break;
            case 'h': case'H': prwEdgeImage(); break;
            case 'i': case'I': sobelVEdgeImage(); break;
            case 'j': case'J': sobelHEdgeImage(); break;
            case 'k': case'K': sobelEdgeImage(); break;
            case 'l': case'L': lapla4EdgeImage(); break;
            case 'm': case'M': laplam8EdgeImage(); break;
            case 'n': case'N': lapla8EdgeImage(); break;
            case 'o': case'O': logEdgeImage(); break;
            case 'v': case'V': dogEdgeImage(); break;
            case 'q': case'Q': usaImage(); break;
            case 'r': case'R': minusImage(); break;


            default:
                if (input != 'x' && input != 'X') printf("-> �ùٸ� ���� �Է��ϼ���.\n"); break;
            }

        }
        else if (menuInput == 4) {
            switch (input) {
            case '>': menuInput++; system("cls"); break;
            case '<': menuInput--; system("cls"); break;
            case '0': openImage(); break;
            case '1': saveImage(); break;
            case '2':equalImage(); break;
            case '3': free2D(m_InImage, m_inH); free2D(m_OutImage, m_outH); return 0;

            case 'a': case'A': histImage(); break;
            case 'b': case'B': histStretchImage(); break;
            case 'c': case'C': histEqualizeImage(); break;


            default:
                if (input != 'x' && input != 'X') printf("-> �ùٸ� ���� �Է��ϼ���.\n"); break;
            }

        }
    }
    system("cls");
    printf("����Ǿ����ϴ�.\n");
    free2D(m_InImage, m_inH); free2D(m_OutImage, m_outH);
    return 0;
}

/// �Լ� ���Ǻ� (�����Լ�)
// �޸� �����Լ�
UC** malloc2D(int  h, int w) {
    UC** mem;
    mem = (UC**)malloc(h * sizeof(UC*));
    for (int i = 0; i < h; i++)
        mem[i] = (UC*)malloc(w * sizeof(UC));

    // �ʱ�ȭ(Clear)
    for (int i = 0; i < h; i++) {
        for (int k = 0; k < w; k++) {
            mem[i][k] = 0;
        }
    }
    return mem;
}
void free2D(UC** memory, int h) {
    if (memory != NULL) {
        for (int i = 0; i < h; i++)
            free(memory[i]);
        free(memory);
    }
}
// - �̹��� ����
void openImage() {
    char input[50];
    char routeName[100] = "c:/images/meRAW/";
    printf("��� ���� �� -> "); scanf("%s", &input);
    strcat(routeName, input); strcat(routeName, ".raw");
    FILE* file = fopen(routeName, "rb");
    if (file == NULL) return;

    //���� �Է� �޸� ����
    free2D(m_InImage, m_inH);
    fseek(file, 0L, SEEK_END);
    unsigned long size = ftell(file);
    fclose(file);

    m_inH = m_inW = (int)sqrt(size);
    m_InImage = malloc2D(m_inH, m_inW);
    printf("[%s][%dx%d]��� ������ ���� �� ..\n", routeName, m_inH, m_inW);
    file = fopen(routeName, "rb");
    for (int i = 0; i < m_inH; i++)
        fread(m_InImage[i], sizeof(UC), m_inW, file);
    fclose(file);
    equalImage();
}
// - �̹��� ����
void saveImage() {
    char input[50];
    char routeName[100] = "c:/images/meRAW/";
    printf("������ ���� �� -> "); scanf("%s", &input);
    strcat(routeName, input); strcat(routeName, ".raw");
    FILE* file = fopen(routeName, "wb");
    for (int i = 0; i < m_outH; i++) {
        fwrite(m_OutImage[i], sizeof(UC), m_outW, file);
    }
    fclose(file);
    MessageBox(hwnd, L"����Ϸ�", L"�޼��� â", NULL);
}
// - �̹��� ��� : Output Image�� �����ش�.
void displayImage() {
    system("cls");
    int px;
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            px = m_OutImage[i][k];
            SetPixel(hdc, k + 630, i + 50, RGB(px, px, px));
        }
    }
}

/// �Լ� ���Ǻ� (����ó��)

//ȭ����ó��
// - �̹��� ����ȭ : Input Image�� Output Image�� �ʱ�ȭ�����ش�.
void equalImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            m_OutImage[i][k] = m_InImage[i][k];
        }
    }
    displayImage();
}
// - ���� �������� �̹��� ��� ���� : ����, ��ο�κ� ���� �Ȱ��� ������ ��ħ.
void pmLightImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    int input = 0;
    printf("���ϴ� ��������� :"); scanf("%d", &input);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            m_OutImage[i][k] += input;
            if ((m_InImage[i][k] + input) > 255) m_OutImage[i][k] = 255;
            else if ((m_InImage[i][k] + input) <= 0) m_OutImage[i][k] = 0;
            else m_OutImage[i][k] = m_InImage[i][k] + input;
        }
    }
    displayImage();
}
// - ���� ���������� �̹��� ��� ���� : ����, ��ο�κ��� ������ ������ ��ħ.
void mdLightImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    int input = 0;
    printf("(1)���� (2) ������ :"); scanf("%d", &input);
    if (input == 1) {
        printf("���ϴ� ��������� :"); scanf("%d", &input);
        for (int i = 0; i < m_inH; i++) {
            for (int k = 0; k < m_inW; k++) {
                if ((m_InImage[i][k] * input) > 255) m_OutImage[i][k] = 255;
                else if ((m_InImage[i][k] * input) <= 0) m_OutImage[i][k] = 0;
                else m_OutImage[i][k] = m_InImage[i][k] * input;
            }
        }
    }
    if (input == 2) {
        printf("���ϴ� ��������� :"); scanf("%d", &input);
        for (int i = 0; i < m_inH; i++) {
            for (int k = 0; k < m_inW; k++) {
                if (input == 0) input = 1;
                if ((m_InImage[i][k] / input) > 255) m_OutImage[i][k] = 255;
                else if ((m_InImage[i][k] / input) <= 0) m_OutImage[i][k] = 0;
                else m_OutImage[i][k] = m_InImage[i][k] / input;
            }
        }
    }

    displayImage();
}
// - ��� ���� AND������ �ϴ� �Լ��̴�. ��Ʈ�������� ó���ϸ� �������� �Ͼ�� �; �������.
// -- 128ũ���� ���� �ش� �̹��� ũ��� ����ũ��� ���� �� ��Ʈ���� ó���Ѵ�.
void andCircleImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);

    //128x128�������� ���� �׸��� �����´�.
    char routeName[100] = "C:/images/meRAW/circle128.raw";
    FILE* file = fopen(routeName, "rb");
    if (file == NULL) return;
    //���� �� ����� ����
    fseek(file, 0L, SEEK_END);
    unsigned long size = ftell(file);
    int c_H, c_W;
    c_H = c_W = (int)sqrt(size);
    fclose(file);
    UC** circ = malloc2D(c_H, c_W); // ���׸� ���� �޸�
    //128x128 ���� �׸���
    file = fopen(routeName, "rb");
    for (int i = 0; i < c_H; i++)
        fread(circ[i], sizeof(UC), c_W, file);
    fclose(file);
    //����� �� �����
    UC** circOut = malloc2D(m_outH, m_outW); // �����Ҷ� ����� ���׸� �޸�
    int scale = (int)(m_outH / c_H);
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            circOut[i][k] = circ[i / scale][k / scale];
        }
    }
    // AND���� :: ����! ��Ʈ�����ڴ� �켱������ ���⶧���� ��ȣó�� �ſ� �߿�
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            if ((m_InImage[i][k] & circOut[i][k]) >= 255)  m_OutImage[i][k] = 255;
            else if ((m_InImage[i][k] & circOut[i][k]) < 0)  m_OutImage[i][k] = 0;
            else m_OutImage[i][k] = (m_InImage[i][k] & circOut[i][k]);
        }
    }
    free2D(circ, c_H);
    free2D(circOut, m_outH);
    displayImage();
}
// ��� ���� OR������ �ϴ� �Լ��̴�.
void orCircleImage() { // ��� ���� OR������ �ϴ� �Լ��̴�.
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);

    //128x128�������� ���� �׸��� �����´�.
    char routeName[100] = "C:/images/meRAW/circle128.raw";
    FILE* file = fopen(routeName, "rb");
    if (file == NULL) return;
    //���� �� ����� ����
    fseek(file, 0L, SEEK_END);
    unsigned long size = ftell(file);
    int c_H, c_W;
    c_H = c_W = (int)sqrt(size);
    fclose(file);
    UC** circ = malloc2D(c_H, c_W); // ���׸� ���� �޸�
    //128x128 ���� �׸���
    file = fopen(routeName, "rb");
    for (int i = 0; i < c_H; i++)
        fread(circ[i], sizeof(UC), c_W, file);
    fclose(file);
    //����� �� �����
    UC** circOut = malloc2D(m_outH, m_outW); // �����Ҷ� ����� ���׸� �޸�
    int scale = (int)(m_outH / c_H);
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            circOut[i][k] = circ[i / scale][k / scale];
        }
    }
    // AND���� :: ����! ��Ʈ�����ڴ� �켱������ ���⶧���� ��ȣó�� �ſ� �߿�
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            if ((m_InImage[i][k] | circOut[i][k]) >= 255)  m_OutImage[i][k] = 255;
            else if ((m_InImage[i][k] | circOut[i][k]) < 0)  m_OutImage[i][k] = 0;
            else m_OutImage[i][k] = (m_InImage[i][k] | circOut[i][k]);
        }
    }
    free2D(circ, c_H);
    free2D(circOut, m_outH);
    displayImage();
}
// - �̹��� ���� ���
void bwImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            if (m_InImage[i][k] > 127) m_OutImage[i][k] = 255;
            else m_OutImage[i][k] = 0;
        }
    }
    displayImage();
}
// - �̹��� ��հ� ���
void bwAvgImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);

    unsigned long hap = 0;
    int cnt = 0;
    int avg = 0;

    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            hap += m_InImage[i][k];
            cnt++;
        }
    }
    avg = (int)hap / cnt;
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            if (m_InImage[i][k] >= avg) m_OutImage[i][k] = 255;
            else m_OutImage[i][k] = 0;
        }
    }
    displayImage();
}
// - �̹��� ����
void ngtvImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            m_OutImage[i][k] = 255 - m_InImage[i][k];
        }
    }
    displayImage();
}
// - �̹��� ���� ����
void gammaImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);

    float gamma;
    printf("������ (0.2~1.8) : "); scanf("%f", &gamma);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            double m = m_InImage[i][k];
            m_OutImage[i][k] = (unsigned int)255.0 * pow(m / 255.0, gamma);
        }
    }
    displayImage();
}
// - �̹��� �Ķ󺼶� ���(Cup, Cap)
void paraImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH; m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);

    char input = 0;
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            //pow()// �ŵ����� : x�� y����
            double value = 255.0 - 255.0 * pow((m_InImage[i][k] / 128.0 - 1.0), 2); //������ ��ü��
            if (value > 255.0) value = 255.0;
            else if (value < 0.0) value = 0.0;

            m_OutImage[i][k] = (UC)value;
        }
    }
    displayImage();
}

///������ ó��
// ���� ��� �˰���
void zoomOutImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    int scale = 0;
    printf("���ϴ� ��ҹ��� :"); scanf("%d", &scale);
    m_outH = m_inH / scale;
    m_outW = m_inW / scale;

    m_OutImage = malloc2D(m_outH, m_outW);

    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            m_OutImage[i / scale][k / scale] = m_InImage[i][k];
        }
    }
    displayImage();
}
// ���� Ȯ�� �˰���
void zoomInImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    int scale = 0;
    printf("���ϴ� Ȯ����� :"); scanf("%d", &scale);
    m_outH = m_inH * scale;
    m_outW = m_inW * scale;

    m_OutImage = malloc2D(m_outH, m_outW);

    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            m_OutImage[i * scale][k * scale] = m_InImage[i][k];
        }
    }
    displayImage();
}
// ���� Ȯ�� ����� �˰���
void zoomInBackImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    int scale = 0;
    printf("���ϴ� Ȯ����� :"); scanf("%d", &scale);
    m_outH = m_inH * scale;
    m_outW = m_inW * scale;

    m_OutImage = malloc2D(m_outH, m_outW);

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            m_OutImage[i][k] = m_InImage[i / scale][k / scale];
        }
    }
    displayImage();
}
// ȸ�� �˰���  : �̿ϼ� (1. �߾�����, 2. ����� 3. ���� ����)
void rotateImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    // ��� ���� �޸� �Ҵ�
    m_OutImage = malloc2D(m_outH, m_outW);
    int angle = 0; // 0~360
    printf("���ϴ� ȸ������ :"); scanf("%d", &angle);

    double radian = angle * M_PI / 180.0;
    // �ﰢ�Լ� ���� :
    // newX = cos * x - sin * y;
    // newY = sin * x + cos * y;
    // ��ǻ�ʹ� radian�ۿ� �ȹ��� (degree���� radian���� ����ȯ ������Ѵ�)

    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {

            int newI = cos(radian) * i - sin(radian) * k;
            int newK = sin(radian) * i + cos(radian) * k;
            if (((0 <= newI) && (newI < m_outH)) && ((0 <= newK) && (newK < m_outW)))
                m_OutImage[newI][newK] = m_InImage[i][k];
        }
    }
    displayImage();
}
// ȸ���˰��� �߽��� : �߾�ȸ�� + �����
void midRotateImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    // ��� ���� �޸� �Ҵ�
    m_OutImage = malloc2D(m_outH, m_outW);
    int angle = 0; // 0~360
    printf("���ϴ� �Ϲ� ȸ������ :"); scanf("%d", &angle);
    double radian = angle * M_PI / 180.0;
    // �ﰢ�Լ� ���� :
    // newX = cos * x - sin * y;
    // newY = sin * x + cos * y;
    // ��ǻ�ʹ� radian�ۿ� �ȹ��� (degree���� radian���� ����ȯ ������Ѵ�)

    // �߾���ġ ���ϱ�
    int cx = m_outH / 2;
    int cy = m_outW / 2;

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {

            int oldI = (cos(radian) * (i - cx) + sin(radian) * (k - cy)) + cx;
            int oldK = (-sin(radian) * (i - cx) + cos(radian) * (k - cy)) + cy;
            if (((0 <= oldI) && (oldI < m_outH)) && ((0 <= oldK) && (oldK < m_outW)))
                m_OutImage[i][k] = m_InImage[oldI][oldK];
        }
    }
    displayImage();
}
// ȸ���˰��� �߽��� : �߾�ȸ�� + ����� + Ȯ�� + ���ۺ����߾ӿ���ȸ��
void midRotateFullImage() {// ���� ȸ�� �˰���. �߾�ȸ��+�����+Ȯ��
	// ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    // ��¥ ���� ó�� �˰���
    int angle; // 0 ~ 360
    printf("���ϴ� ȸ������ :"); scanf("%d", &angle);
    double tmp_radian = angle % 90 * M_PI / 180.0;
    double tmp_radian90 = (90 - angle % 90) * M_PI / 180.0;

    //(�߿�!) ��� ������ ���̿� ���� ���� --> �˰��� ����
    m_outH = (int)(m_inH * cos(tmp_radian90) + m_inW * cos(tmp_radian));
    m_outW = (int)(m_inW * cos(tmp_radian) + m_inW * cos(tmp_radian90));
    // ��� ���� �޸� �Ҵ�
    double radian = angle * 3.141592 / 180.0;
    m_OutImage = malloc2D(m_outH, m_outW);

    // �ӽ� �Է� ���� ---> ��°� ũ�Ⱑ ���� �ϰ�, �Է� ������ �߾ӿ� �α�.
    UC** tmpInput = malloc2D(m_outH, m_outW);
    int dx = (m_outH - m_inH) / 2;
    int dy = (m_outW - m_inW) / 2;
    for (int i = 0; i < m_inH; i++)
        for (int k = 0; k < m_inW; k++)
            tmpInput[i + dx][k + dy] = m_InImage[i][k];

    // �߾� ��ġ ���ϱ�
    int cx = m_outH / 2;
    int cy = m_outW / 2;
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            int oldI = (cos(radian) * (i - cx) + sin(radian) * (k - cy)) + cx;
            int oldK = (-sin(radian) * (i - cx) + cos(radian) * (k - cy)) + cy;
            if (((0 <= oldI) && (oldI < m_outH)) && ((0 <= oldK) && (oldK < m_outW)))
                m_OutImage[i][k] = tmpInput[oldI][oldK];
        }
    }
    free2D(tmpInput, m_outH);
    displayImage();
}
void mirrorLRImage() { //�¿� �̷��� �Լ�
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            m_OutImage[i][k] = m_InImage[i][m_inW - k - 1];
        }
    }
    displayImage();
}
void mirrorUDImage() { //���� �̷��� �Լ�
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            m_OutImage[i][k] = m_InImage[m_inH - i - 1][k];
        }
    }
    displayImage();
}
void moveImage() { //�̵� �̹��� �Լ�
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    int input = 0;
    printf("���ϴ� �̵� ���� : "); scanf("%d", &input);
    if (m_inH < input) input = 0;
    for (int i = input; i < m_inH; i++) {
        for (int k = input; k < m_inW; k++) {

            m_OutImage[i][k] = m_InImage[i-input][k-input];
        }
    }
    displayImage();
}

/// ȭ�ҿ���ó��
double** malloc2D_double(int  h, int w) {
    double** mem;
    mem = (double**)malloc(h * sizeof(double*));
    for (int i = 0; i < h; i++)
        mem[i] = (double*)malloc(w * sizeof(double));

    // �ʱ�ȭ(Clear)
    for (int i = 0; i < h; i++) {
        for (int k = 0; k < w; k++) {
            mem[i][k] = 0;
        }
    }
    return mem;
}
void free2D_double(double** memory, int h) {
    if (memory != NULL) {
        for (int i = 0; i < h; i++)
            free(memory[i]);
        free(memory);
    }
}
// ������ �˰���
void embossImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (������)
    double mask[3][3] = { {-1.,0.,0.},
                          {0.,0.,0.},
                          {0.,0.,1.} };
    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k]; // �ӽ�Input�� �߽ɿ� ������ �ִ���.
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S; // ����ũ9�� X �Է¿��� 9���� ��
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    // ������ (�ٵ��) --> ����ũ�հ谡 0 �Ǵ� 1 �̸� 127 ���ϱ�
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            tmpOutput[i][k] += 127.0;
        }
    }
    // tmpOutput -> m_OutImage // �����÷ο�, ����÷ο� Ȯ�� ��.
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 3x3���� �˰���
void blur3Image() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double mask[3][3] = { {1 / 9.,1 / 9.,1 / 9.},
                          {1 / 9.,1 / 9.,1 / 9.},
                          {1 / 9.,1 / 9.,1 / 9.} };
    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    //// ������ (�ٵ��) --> ����ũ�հ谡 0 �Ǵ� 1 �̸� 127 ���ϱ�
    //for (int i = 0; i < m_outH; i++) {
    //    for (int k = 0; k < m_outW; k++) {
    //        tmpOutput[i][k] += 127.0;
    //    }
    //}
    // tmpOutput -> m_OutImage // �����÷ο�, ����÷ο� Ȯ�� ��.
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 5x5���� �˰���
void blur5Image() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double mask[5][5] = { {1 / 25.,1 / 25.,1 / 25.,1 / 25.,1 / 25.},
                          {1 / 25.,1 / 25.,1 / 25.,1 / 25.,1 / 25.},
                          {1 / 25.,1 / 25.,1 / 25.,1 / 25.,1 / 25.},
                          {1 / 25.,1 / 25.,1 / 25.,1 / 25.,1 / 25.},
                          {1 / 25.,1 / 25.,1 / 25.,1 / 25.,1 / 25.} };
    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 4, m_inW + 4); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 2][k + 2] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ25�� X �Է¿��� 25���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 5; m++) {
                for (int n = 0; n < 5; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    //// ������ (�ٵ��) --> ����ũ�հ谡 0 �Ǵ� 1 �̸� 127 ���ϱ�
    //for (int i = 0; i < m_outH; i++) {
    //    for (int k = 0; k < m_outW; k++) {
    //        tmpOutput[i][k] += 127.0;
    //    }
    //}
    // tmpOutput -> m_OutImage // �����÷ο�, ����÷ο� Ȯ�� ��.
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 4);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// �Է°���� ��ó��
void blurImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    int input = 0;
    printf("�� ���� : "); scanf("%d", &input);
    if (input % 2 == 0) {
        input += 1;
    }
    printf("%d x %d �� ó�� ��...\n", input, input);
    double** mask = malloc2D_double(input, input);
    for (int i = 0; i < input; i++) {
        for (int k = 0; k < input; k++) {
            mask[i][k] = (double)(1.0 / ((double)(input * input)));
        }
    }
    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + (int)(input / 2) * 2, m_inW + (int)(input / 2) * 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + (int)(input / 2)][k + (int)(input / 2)] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < input; m++) {
                for (int n = 0; n < input; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }
    //// ������ (�ٵ��) --> ����ũ�հ谡 0 �Ǵ� 1 �̸� 127 ���ϱ�
    //for (int i = 0; i < m_outH; i++) {
    //    for (int k = 0; k < m_outW; k++) {
    //        tmpOutput[i][k] += 127.0;
    //    }
    //}
    // tmpOutput -> m_OutImage // �����÷ο�, ����÷ο� Ȯ�� ��.

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + (int)(input / 2) * 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// ����þ� ��ó��
void gausBlur3Image() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double mask[3][3] = { {1 / 16.,1 / 8.,1 / 16.},
                          {1 / 8.,1 / 4.,1 / 8.},
                          {1 / 16.,1 / 8.,1 / 16.} };
    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    //// ������ (�ٵ��) --> ����ũ�հ谡 0 �Ǵ� 1 �̸� 127 ���ϱ�
    //for (int i = 0; i < m_outH; i++) {
    //    for (int k = 0; k < m_outW; k++) {
    //        tmpOutput[i][k] += 127.0;
    //    }
    //}
    // tmpOutput -> m_OutImage // �����÷ο�, ����÷ο� Ȯ�� ��.
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// ���������������1
void sharp1Image() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    int input = 0;
    double mask[3][3] = { {-1.,-1.,-1.},
                          {-1., 9.,-1.},
                          {-1.,-1.,-1.} };
    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    //// ������ (�ٵ��) --> ����ũ�հ谡 0 �Ǵ� 1 �̸� 127 ���ϱ�
    //for (int i = 0; i < m_outH; i++) {
    //    for (int k = 0; k < m_outW; k++) {
    //        tmpOutput[i][k] += 127.0;
    //    }
    //}
    // tmpOutput -> m_OutImage // �����÷ο�, ����÷ο� Ȯ�� ��.
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// ���������������2
void sharp2Image() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double mask[3][3] = { {0.,-1.,0},
                          {-1., 5.,-1.},
                          {0,-1.,0.} };
    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    //// ������ (�ٵ��) --> ����ũ�հ谡 0 �Ǵ� 1 �̸� 127 ���ϱ�
    //for (int i = 0; i < m_outH; i++) {
    //    for (int k = 0; k < m_outW; k++) {
    //        tmpOutput[i][k] += 127.0;
    //    }
    //}
    // tmpOutput -> m_OutImage // �����÷ο�, ����÷ο� Ȯ�� ��.
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// ������ ���� ������
void hfSharpImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double mask[3][3] = { {-1. / 9.,1 / 9.,-1. / 9.},
                          {-1. / 9.,8. / 9.,-1. / 8.},
                          {-1. / 9.,1 / 9.,-1. / 9.} };
    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    //// ������ (�ٵ��) --> ����ũ�հ谡 0 �Ǵ� 1 �̸� 127 ���ϱ�
    //for (int i = 0; i < m_outH; i++) {
    //    for (int k = 0; k < m_outW; k++) {
    //        tmpOutput[i][k] += 127.0;
    //    }
    //}
    // tmpOutput -> m_OutImage // �����÷ο�, ����÷ο� Ȯ�� ��.
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}

/// �������� ����
// �������� ����
void vEdgeImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double mask[3][3] = { {0,0,0},
                          {-1,1,0},
                          {0,0,0} };
    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    //// ������ (�ٵ��) --> ����ũ�հ谡 0 �Ǵ� 1 �̸� 127 ���ϱ�
    //for (int i = 0; i < m_outH; i++) {
    //    for (int k = 0; k < m_outW; k++) {
    //        tmpOutput[i][k] += 127.0;
    //    }
    //}
    // tmpOutput -> m_OutImage // �����÷ο�, ����÷ο� Ȯ�� ��.
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// ������ ����
void hEdgeImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double mask[3][3] = { {0,-1,0},
                          {0,1,0},
                          {0,0,0} };
    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    //// ������ (�ٵ��) --> ����ũ�հ谡 0 �Ǵ� 1 �̸� 127 ���ϱ�
    //for (int i = 0; i < m_outH; i++) {
    //    for (int k = 0; k < m_outW; k++) {
    //        tmpOutput[i][k] += 127.0;
    //    }
    //}
    // tmpOutput -> m_OutImage // �����÷ο�, ����÷ο� Ȯ�� ��.
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// ���� ������ ���� (�ؾ���)
/// 1�� �̺а���
// ���� �ι��� ����
void robertsHEdgeImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double mask[3][3]
        = { {-1,0,0} ,
            {0,1,0} ,
            {0,0,0} };

    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// ���� �ι��� ����
void robertsVEdgeImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double mask[3][3]
        = { {0,0,-1} ,
            {0,1,0} ,
            {0,0,0} };

    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// �������,�ι��� ����
void robertsEdgeImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double maskV[3][3]
        = { {-1,0,0} ,
            {0,1,0} ,
            {0,0,0} };
    double maskH[3][3]
        = { {0,0,-1} ,
            {0,1,0} ,
            {0,0,0} };

    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    double** tmpOutput2 = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * maskH[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }
    S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * maskV[m][n];
                }
            }
            tmpOutput2[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v1 = tmpOutput[i][k];
            double v2 = tmpOutput[i][k];
            double v = v1 + v2;
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    free2D_double(tmpOutput2, m_outH);
    displayImage();
}
// ���� ������ ����
void prwVEdgeImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double mask[3][3]
        = { {-1,0,1} ,
            {-1,0,1} ,
            {-1,0,1} };

    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// ���� �����m ����
void prwHEdgeImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double mask[3][3]
        = { {1,1,1} ,
            {0,0,0} ,
            {-1,-1,-1} };

    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// �������,�����m ����
void prwEdgeImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double maskV[3][3]
        = { {-1,0,1} ,
            {-1,0,1} ,
            {-1,0,1} };
    double maskH[3][3]
        = { {1,1,1} ,
            {0,0,0} ,
            {-1,-1,-1} };


    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    double** tmpOutput2 = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * maskH[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }
    S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * maskV[m][n];
                }
            }
            tmpOutput2[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v1 = tmpOutput[i][k];
            double v2 = tmpOutput[i][k];
            double v = v1 + v2;
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    free2D_double(tmpOutput2, m_outH);
    displayImage();
}
// ���� �Һ� ����
void sobelVEdgeImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double mask[3][3]
        = { {1,2,1} ,
            {0,0,0} ,
            {-1,-2,-1} };

    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// ���� �Һ� ����
void sobelHEdgeImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double mask[3][3]
        = { {-1,0,1} ,
            {-2,0,2} ,
            {-1,0,1} };

    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// ������� �Һ� ����
void sobelEdgeImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double maskV[3][3]
        = { {1,2,1} ,
            {0,0,0} ,
            {-1,-2,-1} };
    double maskH[3][3]
        = { {-1,0,1} ,
           {-2,0,2} ,
           {-1,0,1} };

    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    double** tmpOutput2 = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * maskH[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }
    S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * maskV[m][n];
                }
            }
            tmpOutput2[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v1 = tmpOutput[i][k];
            double v2 = tmpOutput[i][k];
            double v = v1 + v2;
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    free2D_double(tmpOutput2, m_outH);
    displayImage();
}
/// 2�� �̺а���
// ���ö�þ�(4) ����
// ���ö�þ��� ȸ������ũ ���� 0��� �Ѵ�.
void lapla4EdgeImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double mask[3][3]
        = { {0,-1,0} ,
            {-1,4,-1} ,
            {0,-1,0} };

    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// ���ö�þ�(-8) ����
void laplam8EdgeImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double mask[3][3]
        = { {1,1,1} ,
            {1,-8,1} ,
            {1,1,1} };

    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// ���ö�þ�(8)  ����
void lapla8EdgeImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double mask[3][3]
        = { {-1,-1,-1} ,
            {-1,8,-1} ,
            {-1,-1,-1} };

    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}

// LoG �������� : 1.����þ� 2. ���ö�þ�
// LoG (Laplacian of Gausian)
// ������ �ΰ��� ���ö�þ��� ������ ����ϰ���, 
// ����þ� ������(����)�� ���� ���ö�þ� ���.
void logEdgeImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double mask[5][5]
        = { {0,0,-1,0,0} ,
            {0,-1,-2,-1,0} ,
            {-1,-2,16,-2,-1},
            {0,-1,-2,-1,0} ,
            {0,0,-1,0,0} };

    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 4, m_inW + 4); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 2][k + 2] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 5; m++) {
                for (int n = 0; n < 5; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 4);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// DoG �������� : LoG�� �����ӵ��� �����ϱ����� ����.
void dogEdgeImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(�߿�!) ȭ�ҿ��� �˰��� �ش��ϴ� ����ũ (����) : �ȼ�/����ũ ��üũ�� 
    double mask[9][9]
        = { {0,0,0,-1,-1,-1,0,0,0},
            {0,-2,-3,-3,-3,-3,-3,-2,0},
            {0,-3,-2,-1,-1,-1,-2,-3,0},
            {0,-3,-1,9,9,9,-1,-3,0},
            {-1,-3,-1,9,19,9,-1,-3,-1},
            {0,-3,-1,9,9,9,-1,-3,0},
            {0,-3,-2,-1,-1,-1,-2,-3,0},
            {0,-2,-3,-3,-3,-3,-3,-2,0},
            {0,0,0,-1,-1,-1,0,0,0}
    };

    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 8, m_inW + 8); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 4][k + 4] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 9; m++) {
                for (int n = 0; n < 9; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 8);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}

// ���翬����
double doubleABS(double x) {
    // �Ǽ��� ���� �� ���� �Լ�
    if (x >= 0) return x;
    else        return -x;
}
void usaImage(){
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double max = 0.0; // ����� �̵��� �� ���� �ִ밪
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            max = 0.0; // �ִ밪�� �ʱ�ȭ
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    if (doubleABS(tmpInput[i + 1][k + 1] -
                        tmpInput[i + m][k + n]) >= max)
                        // ����� ����밪 - ����� �ֺ� �ȼ����� ���밪 �߿���
                        // �ִ밪�� ã�´�.
                        max = doubleABS(tmpInput[i + 1][k + 1] - tmpInput[i + m][k + n]);
                }
            }
            tmpOutput[i][k] = max;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// �� ������
void minusImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double max = 0.0; // ����� �̵��� �� ���� �ִ밪
    double mask[4] = {0,};
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            max = 0.0; // �ִ밪 �ʱ�ȭ
            mask[0] = doubleABS(tmpInput[i][k] - tmpInput[i + 2][k + 2]);
            mask[1] = doubleABS(tmpInput[i][k+1] - tmpInput[i + 2][k + 1]);          
            mask[2] = doubleABS(tmpInput[i][k+2] - tmpInput[i + 2][k]);
            mask[3] = doubleABS(tmpInput[i+1][k] - tmpInput[i + 1][k + 2]);
            for (int m = 0; m < 4; m++) {
                if (mask[m] >= max) max = mask[m];
            }
            tmpOutput[i][k] = max;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// ���� Ȯ��, �缱�� ������
void zoomInYSImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    double scale = 0.0;
    printf("���ϴ� Ȯ����� :"); scanf("%lf", &scale);
    m_outH = m_inH * scale;
    m_outW = m_inW * scale;
    double** tempImage = malloc2D_double(m_inH, m_inW);
    m_OutImage = malloc2D(m_outH, m_outW);

    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tempImage[i][k] = (double)m_InImage[i][k];
        }
    }

    double r_H, r_W, s_H, s_W;
    int i_W, i_H;
    double C1, C2, C3, C4;
    int v = 0;
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            r_H = i / scale;
            r_W = k / scale;

            i_H = (int)floor(r_H); // ����. celi = �ø�
            i_W = (int)floor(r_W);

            s_H = r_H - i_H;
            s_W = r_W - i_W;

            if (i_H < 0 || i_H >= (m_inH - 1) || i_W < 0 || i_W >= (m_inW - 1)) {
                    m_OutImage[i][k] = 255;
            }
            else
            {
                C1 = (double)tempImage[i_H][i_W];
                C2 = (double)tempImage[i_H][i_W+1];
                C3 = (double)tempImage[i_H+1][i_W+1];
                C4 = (double)tempImage[i_H+1][i_W];
            }
            v = (UC)(C1 * (1 - s_H) * (1 - s_W) + C2 * s_W * (1 - s_H) 
                + C3 * s_W * s_H + C4 * (1 - s_W) * s_H);
            m_OutImage[i][k] = v;
        }
    }
    free2D_double(tempImage, m_inH);
    displayImage();
}
// ���� ȸ�� �缱�� ������ : �̿ϼ�
void rotateYSImage() {// ���� ȸ�� �˰���. �߾�ȸ��+�����+Ȯ��

    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH); // ������ ���� ���� ������ ��� width,height�� �Է°� �ٸ� �� �ֱ� ������ ������ �������� �ؾ��Ѵ�.


    // ��¥ ����ó�� �˰���

    int angle; // 0~ 360 �ε� ��ǻ�ʹ� radian���� �ν� ���� ��ȯ���־����
    printf("�̵� ���� ũ�� �Է�:\n  ");
    scanf("%d", &angle);



    double radian = (angle * 3.141592) / 180.0;
    double radian90 = ((90 - angle) * 3.141592) / 180.0;  // 90�� �Ѵ� ���� ��� ������� ����
    // newX = cos * x - sin * y  ���� ȸ�� ���� x = i , y = k
    // newY = sin * x + cos * y



    //(�߿�!) ��� ������ ���̿� ���� �����ؾ��Ѵ� --> �˰��� ���� �޶�������

    m_outH = (int)(m_inH * fabs(cos(radian90)) + m_inW * fabs(cos(radian)));     // Ȯ�븦 ���� �Է¹��� �� �� ��� �� ���� ���ؾ� �ؼ� ��ġ�� �Ʒ���
    m_outW = (int)(m_inW * fabs(cos(radian)) + m_inW * fabs(cos(radian90)));   // �Ǽ����� ������ �مf��. �Ǽ��� ���� �� �ֱ� ����  
                                                                                 // cos���� ������ �� �ֱ� ������ fabs�� �Ǽ��϶� ���밪 ������
    // ��� ���� �޸� �Ҵ�

    m_OutImage = malloc2D(m_outH, m_outW);

    // �ӽ� �Է� ���� -----> ��°� ũ�Ⱑ ���� �ϰ� , �Է� ���� �α�

    UC** tmpInput = malloc2D(m_outH, m_outW); // �ӽ� �Է� ���� �޸� �Ҵ� (���ũ��� �Ҵ�) 


    int dx = (m_outW - m_inW) / 2;
    int dy = (m_outH - m_inH) / 2;

    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {

            tmpInput[i + dy][k + dx] = m_InImage[i][k]; // ���������� tmpInput�� �״�� �����ϴµ� tmpInput�� (0,0) ��ǥ���� �߾����� �̵���Ŵ(dy,dx)
            m_OutImage[i][k] = 0;
        }
    }


    // �߾� ��ġ ���ϱ�
    int centerx = m_outW / 2; //ȸ�� ������ �߾�
    int centery = m_outH / 2;

    int x1, x2, y1, y2;
    double rx, ry, p, q, value;


    //for (int i = 0; i < m_outH; i++) { // �����, ������ ��� : ��� �������� for�� ��������
    //	for (int k = 0; k < m_outW; k++) {

    //		int oldI = (cos(radian) * (i - centerx) + sin(radian) * (k - centery)) + centery;  // �߾ӱ��� ȸ���� ���� ���� ���� , ������������� �ٲ� ��ȣ��
    //		int oldK = (-sin(radian) * (i - centerx) + cos(radian) * (k - centery)) + centerx;

    //		if (((0 <= oldI) && (oldI < m_outH)) && ((0 <= oldK) && (oldK < m_outW))) {


    //			tmpOutput[i][k] = tmpInput[oldI][oldK] ;   // �߾ӿ� ���� tmpInput�� �����ش�. 


    //		}
    //		


    //	}
    //}

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {

            // �Ǽ��� ���� rx, ry�� �Է� ���󿡼� ������ �ȼ� ���� �Ǽ� ��ǥ 
            rx = (double)(-sin(radian)) * (i - centerx) + cos(radian) * (k - centery) + centerx;
            ry = (double)(cos(radian)) * (i - centerx) + sin(radian) * (k - centery) + centery;

            if (0 <= rx && rx < m_outW && 0 <= ry && ry < m_outH) {
                // x1, x2, y1, y2�� ����(rx, ry) ��ǥ�� �ѷ��� 4���� �ȼ� ��ǥ�� ��Ÿ����.
                x1 = (int)rx;
                y1 = (int)ry;

                x2 = x1 + 1;
                if (x2 == m_outW) {
                    x2 = m_outW - 1;
                }

                y2 = y1 + 1;
                if (y2 == m_outH) {
                    y2 = m_outH - 1;
                }
                // p�� q�� 0���� 1 ������ ���� ���� �Ǽ��� ���� 
                p = rx - x1;
                q = ry - y1;

                value = (1. - p) * (1. - q) * tmpInput[y1][x1]
                    + p * (1. - q) * tmpInput[y2][x1]
                    + (1. - p) * q * tmpInput[y1][x2]
                    + p * q * tmpInput[y2][x2];


                if (value > 255) {
                    value = 255;
                }
                else if (value < 0) {
                    value = 0;
                }
                m_OutImage[i][k] = (UC)value;
            }

        }
    }

    free2D(tmpInput, m_outH); // �ӽ� �Է� ���� �޸� ����� RAM ���� ���Ͼ
    displayImage();

}

///������׷�
// ������׷� ���
void histImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = 256;
    m_outW = 256;
    int reSize = m_outH * m_outW;
    UC hist[256]; // ������׷� ���
    int LOW = 0;
    int HIGH = 255;
    UC value = 0;

    //�ʱ�ȭ
    for (int i = 0; i < 256; i++) {
        hist[i] = 0;
    }
    //�󵵼� ����
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            value = m_InImage[i][k];
            hist[value]++;
        }
    }
    // ����ȭ
    UC min = 0;// �ּҰ� �ʱ�ȭ
    UC max = 0; // �ִ밪 �ʱ�ȭ
    UC dif;
    int hNum = 0;
    for (int i = 0; i < 256; i++) {
        if (hist[i] <= min) min = (UC)hist[i];
        if (hist[i] >= max) max = (UC)hist[i];
    }
    dif = max - min;
    UC scaleHist[256];
    // ����ȭ �� ������׷�
    for (int i = 0; i < 256; i++) {
        scaleHist[i] = (UC)((hist[i] - min) * HIGH / dif);
    }
    // ����ȭ�� ������׷� ���
    UC* OutImage = (UC*)malloc((reSize) * sizeof(UC));
    // ����ȭ��������׷��ǰ�����¹迭��������(0)����ǥ��
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < scaleHist[i]; k++) {
            OutImage[m_outW * (m_outH - k - 1) + i] = 0;
        }
    }
    hNum = 0;
    m_OutImage = malloc2D(m_outH, m_outW);
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            m_OutImage[i][k] = OutImage[hNum];
            hNum++;
        }
    }
    free(OutImage);
    displayImage();
}
//��Ʈ��Ī : �ܽ�Ʈ��Ʈ�� ���� �̹����� �����ϰ� ���ش�.
void histStretchImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    int LOW = 0;
    int HIGH = 255;
    UC min = (UC)HIGH;// �ּҰ� �ʱ�ȭ
    UC max = (UC)LOW; // �ִ밪 �ʱ�ȭ
    
    //�Է� ������ �ּҰ� ã��
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            if(m_InImage[i][k] <= min) 
                min = m_InImage[i][k];
        }
    }
    //�Է� ������ �ִ밪 ã��
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            if (m_InImage[i][k] >= max)
                max = m_InImage[i][k];
        }
    }
    m_OutImage = malloc2D(m_outH, m_outW);
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            m_OutImage[i][k] = (UC)(m_InImage[i][k]-min)*HIGH/(max-min);
        }
    }
    displayImage();
}
//��Ȱȭ : �ܽ�Ʈ��Ʈ�� �뷱���� �¾�����.
// ��Ȱȭ�� ������׷� ������ ���̸� �����ϰ��ϴ°�.
// != ��Ʈ��Ī�� ������׸� ������ ���̴� �����ϸ� �а� ��ġ�°�.
void histEqualizeImage() {
    // ���� ��� �޸� ����
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;

    int i, j, vmax, vmin;
    double m_HIST[256];
    double m_Sum_of_HIST[256];
    int value;
    unsigned char LOW, HIGH, Temp;
    double SUM = 0.0;

    int size = m_inH * m_inW;
    LOW = 0;
    HIGH = 255;

    // �ʱ�ȭ
    for (int i = 0; i < 256; i++)
        m_HIST[i] = LOW;
    // �󵵼�����
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            value = m_InImage[i][k];
            m_HIST[value]++;
        }
    }
    // ����������׷�����
    for (int i = 0; i < 256; i++) {
        SUM += m_HIST[i];
        m_Sum_of_HIST[i] = SUM;
    }

    m_OutImage = malloc2D(m_outH,m_outW);
    // �Է¿�������Ȱȭ�ȿ����������
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            Temp = m_InImage[i][k];
            m_OutImage[i][k] = (UC)(m_Sum_of_HIST[Temp] * HIGH / size);
        }
    }

    displayImage();
}