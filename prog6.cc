/*
 * Usage of CDK Matrix
 *
 * File:   prog6.cc
 * Author: Stephen Perkins, editted for HW6 by Lucian Jiang-Wei
 * Email:  lxj160030@utdallas.edu
 * CS 3377.502
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include "cdk.h"


#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

class BinFileHeader{
 public:
  uint32_t magicNum;
  uint32_t versionNum;
  uint64_t numRecords;

};

const int maxStrLen = 25;

class BinFile{
 public:
  uint8_t strLen;
  char strBuffer[maxStrLen];
};
int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"f", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"f", "a", "b", "c", "d", "e"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  BinFileHeader *headRecord = new BinFileHeader();

  BinFile *record = new BinFile();

  ifstream binIn ("cs3377.bin", ios::in | ios::binary);

  binIn.read((char *) headRecord, sizeof(BinFileHeader));
  // cout << (int) record->strLen << endl;

  // printf("%d\n", headRecord->versionNum);

  char buffer[100];
  sprintf(buffer, "Magic: 0x%.8X", headRecord->magicNum);
  setCDKMatrixCell(myMatrix, 1, 1, buffer);

  sprintf(buffer, "Version: %d", headRecord->versionNum);
  setCDKMatrixCell(myMatrix, 1, 2, buffer);

  sprintf(buffer, "NumRecords: %d", headRecord->numRecords);
  setCDKMatrixCell(myMatrix, 1, 3, buffer);

  for(int i = 0; i < headRecord->numRecords; i++){
    binIn.read((char *) record, sizeof(BinFile));

    sprintf(buffer, "strlen: %d", record->strLen);
    setCDKMatrixCell(myMatrix, i+2, 1, buffer);
    setCDKMatrixCell(myMatrix, i+2, 2, record->strBuffer);
  }

  drawCDKMatrix(myMatrix, true);
  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
