#include "Board.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <direct.h>
#include <io.h>

#define STR_CAT(x, y) x ## y
#define STR(x) STR_CAT(x, )


int ExtractDigits(const char* string, int num) {
    int LOW = num % 100;
    int HIGH = num / 100;
    if (strcmp(string, "HIGH") == 0)
        return HIGH;
    else if (strcmp(string, "LOW") == 0)
        return LOW;
}

void Board::CreateBoard()
{
    for (int y = 0; y < BOARD_SIZE; y++)
        for (int x = 0; x < BOARD_SIZE; x++)
            board[x][y].state = EMPTY;

    //��l��
    board[BOARD_SIZE / 2][BOARD_SIZE / 2].state = WHITE;
    board[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2].state = BLACK;
    board[BOARD_SIZE / 2][BOARD_SIZE / 2 - 1].state = BLACK;
    board[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 - 1].state = WHITE;
}

void Board::ShowBoard(int wave)
{

    printf("\33[?25l\33[0;0H");//�M���׺�(�h0,0)
    printf("����");
    for (int i = 0; i < BOARD_SIZE; i++)printf("����");

    printf("��\n");

    for (int y = 0; y < BOARD_SIZE; y++)
    {
        printf("�� ");
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (board[x][y].state == EMPTY)
                printf("\33[42m��\33[0m");
            else if (board[x][y].state == BLACK)
                printf("\33[42m��\33[0m");
            else if (board[x][y].state == WHITE)
                printf("\33[42m��\33[0m");
            else if (board[x][y].state == OK)
                printf("\33[42m��\33[0m");//��
            else
                printf("%c", board[x][y].state);
        }
        printf("��\n");
    }
    printf("����");
    for (int i = 0; i < BOARD_SIZE; i++)printf("����");

    printf("��\n");

    if (wave % 2 == 0)
        printf("��");
    else
        printf("��");
    printf("Wave:%d\n", wave);

    int point = BOARD_SIZE * 2 + 6;

    printf("\33[1;%dH��", point);
    printf("����������");
    printf("��");
    printf("\33[2;%dH�� �x�s��", point);
    printf("\33[3;%dH", point);
    printf("��");
    printf("����������");
    printf("��");

    printf("\33[4;%dH��", point);
    printf("����������");
    printf("��");
    printf("\33[5;%dH�� Ū����", point);
    printf("\33[6;%dH", point);
    printf("��");
    printf("����������");
    printf("��");

    printf("\33[7;%dH��", point);
    printf("����������");
    printf("��");
    printf("\33[8;%dH�� �]�w��", point);
    printf("\33[9;%dH", point);
    printf("��");
    printf("����������");
    printf("��");
}

void Board::Judge_0(int x, int y)
{
    int x_original = x, y_original = y;//�O�s��l��m
    char original_state = board[x_original][y_original].state;//��l���
    char opposite_state = ' ';//�ۤϦ��

    if (original_state == BLACK)opposite_state = WHITE;
    else if (original_state == WHITE)opposite_state = BLACK;

    while ((x + 1 < BOARD_SIZE) && (board[x + 1][y].state == original_state) && (original_state == WHITE || original_state == BLACK))
    {
        board[x_original][y_original].judge_0++;
        x++;
    }


    while ((x + 1 < BOARD_SIZE) && board[x + 1][y].state == opposite_state)
    {
        board[x_original][y_original].judge_0 += 100;
        x++;
    }

    if (board[x_original][y_original].judge_0 >= 100)
        board[x_original][y_original].clamp_0++;
}

void Board::Judge_45(int x, int y)
{
    int x_original = x, y_original = y;//�O�s��l��m
    char original_state = board[x_original][y_original].state;//��l���
    char opposite_state = ' ';//�ۤϦ��

    if (original_state == BLACK)opposite_state = WHITE;
    else if (original_state == WHITE)opposite_state = BLACK;

    while ((x + 1 < BOARD_SIZE) && (y > 0) && (board[x + 1][y - 1].state == original_state) && (original_state == WHITE || original_state == BLACK))
    {
        board[x_original][y_original].judge_45++;
        x++; y--;
    }


    while ((x + 1 < BOARD_SIZE) && (y > 0) && board[x + 1][y - 1].state == opposite_state)
    {
        board[x_original][y_original].judge_45 += 100;
        x++; y--;
    }

    if (board[x_original][y_original].judge_45 >= 100)
        board[x_original][y_original].clamp_45++;
}

void Board::Judge_90(int x, int y)
{
    int x_original = x, y_original = y;//�O�s��l��m
    char original_state = board[x_original][y_original].state;//��l���
    char opposite_state = ' ';//�ۤϦ��

    if (original_state == BLACK)opposite_state = WHITE;
    else if (original_state == WHITE)opposite_state = BLACK;

    while ((y > 0) && (board[x][y - 1].state == original_state) && (original_state == WHITE || original_state == BLACK))
    {
        board[x_original][y_original].judge_90++;
        y--;
    }


    while (y > 0 && board[x][y - 1].state == opposite_state)
    {
        board[x_original][y_original].judge_90 += 100;
        y--;
    }

    if (board[x_original][y_original].judge_90 >= 100)
        board[x_original][y_original].clamp_90++;
}

void Board::Judge_135(int x, int y)
{
    int x_original = x, y_original = y;//�O�s��l��m
    char original_state = board[x_original][y_original].state;//��l���
    char opposite_state = ' ';//�ۤϦ��

    if (original_state == BLACK)opposite_state = WHITE;
    else if (original_state == WHITE)opposite_state = BLACK;

    while ((x > 0) && (y > 0) && (board[x - 1][y - 1].state == original_state) && (original_state == WHITE || original_state == BLACK))
    {
        board[x_original][y_original].judge_135++;
        x--; y--;
    }


    while ((x > 0) && (y > 0) && board[x - 1][y - 1].state == opposite_state)
    {
        board[x_original][y_original].judge_135 += 100;
        x--; y--;
    }

    if (board[x_original][y_original].judge_135 >= 100)
        board[x_original][y_original].clamp_135++;
}

void Board::Judge_180(int x, int y)
{
    int x_original = x, y_original = y;//�O�s��l��m
    char original_state = board[x_original][y_original].state;//��l���
    char opposite_state = ' ';//�ۤϦ��

    if (original_state == BLACK)opposite_state = WHITE;
    else if (original_state == WHITE)opposite_state = BLACK;

    while ((x > 0) && (board[x - 1][y].state == original_state) && (original_state == WHITE || original_state == BLACK))
    {
        board[x_original][y_original].judge_180++;
        x--;
    }


    while (x > 0 && board[x - 1][y].state == opposite_state)
    {
        board[x_original][y_original].judge_180 += 100;
        x--;
    }

    if (board[x_original][y_original].judge_180 >= 100)
        board[x_original][y_original].clamp_180++;
}

void Board::Judge_225(int x, int y)
{
    int x_original = x, y_original = y;//�O�s��l��m
    char original_state = board[x_original][y_original].state;//��l���
    char opposite_state = ' ';//�ۤϦ��

    if (original_state == BLACK)opposite_state = WHITE;
    else if (original_state == WHITE)opposite_state = BLACK;

    while ((x > 0) && (y + 1 < BOARD_SIZE) && (board[x - 1][y + 1].state == original_state) && (original_state == WHITE || original_state == BLACK))
    {
        board[x_original][y_original].judge_225++;
        x--; y++;
    }


    while ((x > 0) && (y + 1 < BOARD_SIZE) && board[x - 1][y + 1].state == opposite_state)
    {
        board[x_original][y_original].judge_225 += 100;
        x--; y++;
    }

    if (board[x_original][y_original].judge_225 >= 100)
        board[x_original][y_original].clamp_225++;
}

void Board::Judge_270(int x, int y)
{
    int x_original = x, y_original = y;//�O�s��l��m
    char original_state = board[x_original][y_original].state;//��l���
    char opposite_state = ' ';//�ۤϦ��

    if (original_state == BLACK)opposite_state = WHITE;
    else if (original_state == WHITE)opposite_state = BLACK;

    while ((y + 1 < BOARD_SIZE) && (board[x][y + 1].state == original_state) && (original_state == WHITE || original_state == BLACK))
    {
        board[x_original][y_original].judge_270++;
        y++;
    }


    while (y + 1 < BOARD_SIZE && board[x][y + 1].state == opposite_state)
    {
        board[x_original][y_original].judge_270 += 100;
        y++;
    }

    if (board[x_original][y_original].judge_270 >= 100)
        board[x_original][y_original].clamp_270++;
}

void Board::Judge_315(int x, int y)
{
    int x_original = x, y_original = y;//�O�s��l��m
    char original_state = board[x_original][y_original].state;//��l���
    char opposite_state = ' ';//�ۤϦ��

    if (original_state == BLACK)opposite_state = WHITE;
    else if (original_state == WHITE)opposite_state = BLACK;

    while ((x + 1 < BOARD_SIZE) && (y + 1 < BOARD_SIZE) && (board[x + 1][y + 1].state == original_state) && (original_state == WHITE || original_state == BLACK))
    {
        board[x_original][y_original].judge_315++;
        x++; y++;
    }


    while ((x + 1 < BOARD_SIZE) && (y + 1 < BOARD_SIZE) && board[x + 1][y + 1].state == opposite_state)
    {
        board[x_original][y_original].judge_315 += 100;
        x++; y++;
    }

    if (board[x_original][y_original].judge_315 >= 100)
        board[x_original][y_original].clamp_315++;
}

void Board::JudgeBoard(int wave)
{
    for (int y = 0; y < BOARD_SIZE; y++)
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            board[x][y].judge_0 = 0;
            board[x][y].judge_45 = 0;
            board[x][y].judge_90 = 0;
            board[x][y].judge_135 = 0;
            board[x][y].judge_180 = 0;
            board[x][y].judge_225 = 0;
            board[x][y].judge_270 = 0;
            board[x][y].judge_315 = 0;

            board[x][y].clamp_0 = 0;
            board[x][y].clamp_45 = 0;
            board[x][y].clamp_90 = 0;
            board[x][y].clamp_135 = 0;
            board[x][y].clamp_180 = 0;
            board[x][y].clamp_225 = 0;
            board[x][y].clamp_270 = 0;
            board[x][y].clamp_315 = 0;
        }

    for (int y = 0; y < BOARD_SIZE; y++)
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            Judge_0(x, y);
            Judge_45(x, y);
            Judge_90(x, y);
            Judge_135(x, y);
            Judge_180(x, y);
            Judge_225(x, y);
            Judge_270(x, y);
            Judge_315(x, y);
        }

    for (int y = 0; y < BOARD_SIZE; y++)
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            int x_original = x, y_original = y;//�O�s��l��m
            char original_state = board[x_original][y_original].state;//��l���
            char opposite_state = ' ';//�ۤϦ��
            char now_state;//�{�b�֭n�U��

            if (original_state == BLACK)opposite_state = WHITE;
            else if (original_state == WHITE)opposite_state = BLACK;


            if (wave % 2 == 0)now_state = WHITE;
            else now_state = BLACK;

            if (now_state == opposite_state)
            {
                if (board[x][y].clamp_0 + board[x][y].clamp_180 == 1)
                {
                    if (board[x][y].clamp_0 == 1)
                    {
                        ChangeBoard(SYSTEM, OK, x - ExtractDigits("LOW", board[x][y].judge_180) - 1, y);
                    }
                    else if (board[x][y].clamp_180 == 1)
                    {
                        ChangeBoard(SYSTEM, OK, x + ExtractDigits("LOW", board[x][y].judge_0) + 1, y);
                    }
                }
                if (board[x][y].clamp_45 + board[x][y].clamp_225 == 1)
                {
                    if (board[x][y].clamp_45 == 1)
                    {
                        ChangeBoard(SYSTEM, OK, x - ExtractDigits("LOW", board[x][y].judge_225) - 1, y + ExtractDigits("LOW", board[x][y].judge_225) + 1);
                    }
                    else if (board[x][y].clamp_225 == 1)
                    {
                        ChangeBoard(SYSTEM, OK, x + ExtractDigits("LOW", board[x][y].judge_45) + 1, y - ExtractDigits("LOW", board[x][y].judge_45) - 1);
                    }
                }
                if (board[x][y].clamp_90 + board[x][y].clamp_270 == 1)
                {
                    if (board[x][y].clamp_90 == 1)
                    {
                        ChangeBoard(SYSTEM, OK, x, y + ExtractDigits("LOW", board[x][y].judge_270) + 1);
                    }
                    else if (board[x][y].clamp_270 == 1)
                    {
                        ChangeBoard(SYSTEM, OK, x, y - ExtractDigits("LOW", board[x][y].judge_90) - 1);
                    }
                }
                if (board[x][y].clamp_135 + board[x][y].clamp_315 == 1)
                {
                    if (board[x][y].clamp_135 == 1)
                    {
                        ChangeBoard(SYSTEM, OK, x + ExtractDigits("LOW", board[x][y].judge_315) + 1, y + ExtractDigits("LOW", board[x][y].judge_315) + 1);
                    }
                    else if (board[x][y].clamp_315 == 1)
                    {
                        ChangeBoard(SYSTEM, OK, x - ExtractDigits("LOW", board[x][y].judge_135) - 1, y - ExtractDigits("LOW", board[x][y].judge_135) - 1);
                    }
                }
            }
        }
}

int Board::ChangeBoard(char who, char state, int x, int y)
{
    if (x >= 0 && y >= 0 && x < BOARD_SIZE && y < BOARD_SIZE)
    {
        if (who == SYSTEM)
            if (board[x][y].state == EMPTY)
                board[x][y].state = state;

        if (who == PLAYER)
            if (board[x][y].state == OK)
            {
                board[x][y].state = state;
                return 1;
            }
    }
    return 0;
}

void Board::RightButtom(int wave, int x, int y)
{

    if (x >= 0 && y >= 0 && x < BOARD_SIZE && y < BOARD_SIZE)
    {
        printf("board[%d][%d].judge_  0:%3d\n", x, y, board[x][y].judge_0);
        printf("board[%d][%d].judge_ 45:%3d\n", x, y, board[x][y].judge_45);
        printf("board[%d][%d].judge_ 90:%3d\n", x, y, board[x][y].judge_90);
        printf("board[%d][%d].judge_135:%3d\n", x, y, board[x][y].judge_135);
        printf("board[%d][%d].judge_180:%3d\n", x, y, board[x][y].judge_180);
        printf("board[%d][%d].judge_225:%3d\n", x, y, board[x][y].judge_225);
        printf("board[%d][%d].judge_270:%3d\n", x, y, board[x][y].judge_270);
        printf("board[%d][%d].judge_315:%3d\n\n", x, y, board[x][y].judge_315);

        printf("board[%d][%d].clamp_  0:%3d\n", x, y, board[x][y].clamp_0);
        printf("board[%d][%d].clamp_ 45:%3d\n", x, y, board[x][y].clamp_45);
        printf("board[%d][%d].clamp_ 90:%3d\n", x, y, board[x][y].clamp_90);
        printf("board[%d][%d].clamp_135:%3d\n", x, y, board[x][y].clamp_135);
        printf("board[%d][%d].clamp_180:%3d\n", x, y, board[x][y].clamp_180);
        printf("board[%d][%d].clamp_225:%3d\n", x, y, board[x][y].clamp_225);
        printf("board[%d][%d].clamp_270:%3d\n", x, y, board[x][y].clamp_270);
        printf("board[%d][%d].clamp_315:%3d\n", x, y, board[x][y].clamp_315);
    }
    else
    {
        printf("\33[31m���X(�L���)\33[0m             \n");
        for (int i = 0; i < 16; i++)//�M���ù�(�U�b)
            printf("                           \n");
    }
}

void Board::ClearOK()
{
    for (int y = 0; y < BOARD_SIZE; y++)
        for (int x = 0; x < BOARD_SIZE; x++)
            if (board[x][y].state == OK)
                board[x][y].state = EMPTY;
}

void Board::Reversal(int wave)//½��
{
    char state = ' ';

    if (wave % 2 == 1)
        state = WHITE;
    else
        state = BLACK;

    for (int y = 0; y < BOARD_SIZE; y++)
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (board_history[x][y][wave].clamp_0 + board_history[x][y][wave].clamp_180 == 1 && board[x][y].clamp_0 + board[x][y].clamp_180 == 2)
                board[x][y].state = state;
            if (board_history[x][y][wave].clamp_45 + board_history[x][y][wave].clamp_225 == 1 && board[x][y].clamp_45 + board[x][y].clamp_225 == 2)
                board[x][y].state = state;
            if (board_history[x][y][wave].clamp_90 + board_history[x][y][wave].clamp_270 == 1 && board[x][y].clamp_90 + board[x][y].clamp_270 == 2)
                board[x][y].state = state;
            if (board_history[x][y][wave].clamp_135 + board_history[x][y][wave].clamp_315 == 1 && board[x][y].clamp_135 + board[x][y].clamp_315 == 2)
                board[x][y].state = state;
        }
}

void Board::SaveToFile(char filename[256])
{
    std::string board_folderPath = "./boards";// ��Ƨ����|
    if (_access(board_folderPath.c_str(), 0) != 0) // �ˬd��Ƨ��O�_�s�b�A�p�G���s�b�N�Ы�
        _mkdir(board_folderPath.c_str());


    std::string folderPath = "./boards/board_" + std::to_string(BOARD_SIZE);// ��Ƨ����|
    if (_access(folderPath.c_str(), 0) != 0) // �ˬd��Ƨ��O�_�s�b�A�p�G���s�b�N�Ы�
        _mkdir(folderPath.c_str());

    std::string newFilename = folderPath + "/" + filename + ".board_" + std::to_string(BOARD_SIZE);// �ק� filename�A�[�W ".board_BOARD_SIZE"
    std::ofstream outFile(newFilename, std::ios::binary);// ���}�G�i���ɮ�

    if (outFile.is_open()) // �ˬd�O�_���\���}�ɮ�
    {
        outFile.write(reinterpret_cast<char*>(this), sizeof(Board));// �g�J board �ƾڵ��c
        outFile.close();
        std::cout << "�ɮפw�O�s���\�C\n" << newFilename << std::endl;
    }
    else
        std::cerr << "�L�k���}�ɮסC\n" << newFilename << std::endl;

    Sleep(100);
    system("cls");// �M���׺�
}



void Board::LoadFromFile(const char* folderPath, uint8_t filenum)
{
    struct _finddata_t fileData;
    intptr_t findHandle;

    std::string searchPath = std::string(folderPath) + "/board_" + std::to_string(BOARD_SIZE) + "/*";
    findHandle = _findfirst(searchPath.c_str(), &fileData);

    if (findHandle == -1) {
        std::cerr << "No files found in directory: " << searchPath << std::endl;
        return;
    }

    int currentFileNum = 0;

    do {
        if (!(fileData.attrib & _A_SUBDIR)) {
            // �p�G���O�l�ؿ��A�B�z���
            std::string filePath = std::string(folderPath) + "/board_" + std::to_string(BOARD_SIZE) + "/" + fileData.name;
            std::cout << fileData.name << std::endl;

            if (currentFileNum < 250) {
                // �N�ɮצW�٫O�s�� struct File file[250]
                file[currentFileNum].num = currentFileNum;
                strncpy(file[currentFileNum].string, fileData.name, sizeof(file[currentFileNum].string) - 1);
                file[currentFileNum].string[sizeof(file[currentFileNum].string) - 1] = '\0';

                if (filenum >= 0 && currentFileNum == filenum) {
                    std::ifstream inFile(filePath.c_str(), std::ios::binary);
                    if (inFile.is_open()) {
                        inFile.read(reinterpret_cast<char*>(this), sizeof(Board));// Ū�� board �ƾڵ��c
                        inFile.close();
                    }
                    else {
                        std::cerr << "Unable to open file for reading: " << filePath << std::endl;
                    }
                    break;
                }
                currentFileNum++;
            }
            else {
                std::cerr << "Too many files found. Maximum limit reached." << std::endl;
                break;
            }
        }
    } while (_findnext(findHandle, &fileData) == 0);

    _findclose(findHandle);
}




void Board::CopyBoard(int wave)
{
    for (int y = 0; y < BOARD_SIZE; y++)
        for (int x = 0; x < BOARD_SIZE; x++)
            board_history[x][y][wave - 1] = board[x][y];
}

int Board::Ending(int wave)
{
    int total = 0;
    for (int y = 0; y < BOARD_SIZE; y++)
        for (int x = 0; x < BOARD_SIZE; x++)
            if (board[x][y].state == WHITE || board[x][y].state == BLACK)
                total++;

    int ok = 0;
    for (int y = 0; y < BOARD_SIZE; y++)
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (board_history[x][y][wave - 1].state == OK)
                ok++;
            if (board_history[x][y][wave - 2].state == OK)
                ok++;

        }
    if (total >= BOARD_SIZE * BOARD_SIZE || ok == 0)
        return 1;

    else
        return 0;
}

int Board::HaveOK()
{
    int total = 0;
    for (int y = 0; y < BOARD_SIZE; y++)
        for (int x = 0; x < BOARD_SIZE; x++)
            if (board[x][y].state == OK)
                total++;
    if (total == 0)
        return 1;
    else
        return 0;
}

int Board::CountBoard(char state)
{
    short int black = 0, white = 0;
    for (int y = 0; y < BOARD_SIZE; y++)
        for (int x = 0; x < BOARD_SIZE; x++)
            if (board[x][y].state == BLACK)
                black++;
            else if (board[x][y].state == WHITE)
                white++;
    if (state == BLACK)
        return black;
    else if (state == WHITE)
        return white;
}