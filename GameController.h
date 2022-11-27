#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include<stdbool.h>



int getPieceToMove(int notToCheck, bool turn, int piece, int pPositions[][2], int oPositions[][2]){
    if (turn){
        for(int i = 0;i < 15; i++){
            if(piece == pPositions[i][1] && pPositions[i][0] != notToCheck){
                return pPositions[i][0];
            }
        }
        
    }else{
        for(int i = 0;i < 15; i++){
            if(piece == oPositions[i][1] && oPositions[i][0] != notToCheck){
                return oPositions[i][0];
            }
        }

    }
    return -1;

}

int countOccurences(int element, int arr[][2], int size){
    int count = 0;
    for(int i = 0; i < size; i++){
        if(arr[i][1] == element){
            count++;
        }
    }
    return count;
}

int whereToPutInBar(bool turn, int bar[][2]){
    if(turn){
        for(int i = 0; i < 30; i++){
            if(bar[i][0] == -99){
                return i;
            }
        }
    }
    else{
        for(int i = 0; i < 30; i++){
            if(bar[i][1] == -99){
                return i;
            }
        }
    }
}

void movePieceToBar(bool turn, int pos, int bar[][2], int oPositions[][2], int pPositions[][2]){
    int pieceIndex = getPieceToMove(-1, turn, pos, oPositions, pPositions);
    if (!turn && pieceIndex != -1){
        oPositions[pieceIndex][1] = -99;
        bar[whereToPutInBar(turn, bar)][1] = pieceIndex;
    }else if(turn && pieceIndex != -1){
        pPositions[pieceIndex][1] = -99;
        bar[whereToPutInBar(turn, bar)][0] = pieceIndex;
    }

}
int checkIfBlot(bool turn, int oPositions[][2], int pPositions[][2]){
    for (int i = 0; i < 15; i++){
        int key = oPositions[i][1];
        for(int j = 0; j < 15; j++){
            if (pPositions[j][1] == key){
                return key;
            }
        }
    }
    return -1;
}

int getBearedOffPieces(bool turn, int oPositions[][2], int pPositions[][2]){
    int count = 0;
    if (turn){
        for (int i = 0; i < 15; i++){
            if (pPositions[i][1] == -99){
                count++;
            }
        }
    }else{
        for (int i = 0; i < 15; i++){
            if (oPositions[i][1] == -99){
                count++;
            }
        }
    }
    return count;

}


bool checkIfPieceIsFromPlayer(bool turn, int piece, int board[], int pPositions[][2], int oPositions[][2]){
    if(turn){
        
        int found = 0;
        for(int i = 0; i < 15; i++){
            if(piece == pPositions[i][1]){
                return true;
            }
        }
        if (found == 0){
            return false;
        }

    }else{
        
        int found = 0;
        for(int i = 0; i < 15; i++){
            if(piece == oPositions[i][1]){
                return true;
            }
        }
        if (found == 0){
            return false;
        }

    }
    return false;
}
bool checkIfOpenPoint(int point, bool turn, int board[], int pPositions[][2], int oPositions[][2]){
    
    if(turn){
        if(countOccurences(point, oPositions, 15) > 1 || point < 0){
            return false;
        }else{
            return true;
        }

    }else{
        if (countOccurences(point, pPositions, 15) > 1 || point > 23){
            return false;
        }
        else{
            return true;
        }

    }
    

}

int equalDiceResult(bool * turn, int board[], int pPositions[][2], int oPositions[][2], int dice[]){
    int tryAgain = 1;
    if(*turn){
        do{
            printf("Which piece will you move %d positions?", dice[0] * 4);
            printf("\n or you can exit[-1]");
            int piece;
            scanf("%d", &piece);
            if (piece == -1){return -1;}
            piece--;
            if(checkIfPieceIsFromPlayer(*turn, piece, board, pPositions, oPositions) ){
                int arrIndexOfPiece = getPieceToMove(-1, *turn, piece, pPositions, oPositions);
                if(checkIfOpenPoint(pPositions[piece][1] - (dice[0] * 4), *turn, board, pPositions, oPositions)){
                    
                    if (arrIndexOfPiece != -1){
                        pPositions[arrIndexOfPiece][1] -=(dice[0] * 4);
                        tryAgain = 0;
                        (*turn) = !(*turn);
                    }else{
                        printf("Cannot find piece. Try again.\n");
                    }
                }else{
                    printf("You can't move to that point, it's occupied by an enemy piece.\n");
                }
            }


        }while(tryAgain == 1);
    }else{
        do{
            printf("Which piece will you move %d positions?", dice[0] * 4);
            printf("\n or you can exit[-1]");
            int piece;
            scanf("%d", &piece);
            if (piece == -1){return -1;}
            piece--;
            if(checkIfPieceIsFromPlayer(*turn, piece, board, pPositions, oPositions) ){
                int arrIndexOfPiece = getPieceToMove(-1, *turn, piece, pPositions, oPositions);
                if(checkIfOpenPoint(oPositions[piece][1] + (dice[0] * 4), *turn, board, pPositions, oPositions)){
                    
                    if (arrIndexOfPiece != -1){
                        oPositions[arrIndexOfPiece][1] +=(dice[0] * 4);
                        tryAgain = 0;
                        (*turn) = !(*turn);
                    }else{
                        printf("Cannot find piece. Try again.\n");
                    }
                }else{
                    printf("You can't move to that point, it's occupied by an enemy piece.\n");
                }
            }


        }while(tryAgain == 1);
    }
    return 0;

}

int samePieceBothResults( bool * turn, int board[], int pPositions[][2], int oPositions[][2], int dice[]){
    int tryAgain = 1;
    if (*turn){
        do{
            printf("Which piece will you move %d positions?", dice[0] + dice[1]);
            printf("or go back[-1]?");

            int piece;
            scanf("%d", &piece);
            if (piece == - 1){return -1;}
            piece--;

            if(checkIfPieceIsFromPlayer(*turn, piece, board, pPositions, oPositions) ){


                int arrIndexOfPiece = getPieceToMove(-1, *turn, piece, pPositions, oPositions);
                if(checkIfOpenPoint(pPositions[arrIndexOfPiece][1] - (dice[0] + dice[1]), *turn, board, pPositions, oPositions)){
                    if (arrIndexOfPiece != -1){
                        pPositions[arrIndexOfPiece][1] -=(dice[0] + dice[1]);
                        tryAgain = 0;
                        (*turn) = !(*turn);
                    }else{
                        printf("Cannot find piece. Try again.\n");
                    }
                }else{
                    printf("You can't move to that point, it's occupied by an enemy piece.\n");
                }
            }

        }while(tryAgain == 1);
    }else{
        do{
            printf("Which piece will you move %d positions?", dice[0] + dice[1]);
            int piece;
            scanf("%d", &piece);
            piece--;
            if(checkIfPieceIsFromPlayer(*turn, piece, board, pPositions, oPositions)){
                int arrIndexOfPiece = getPieceToMove(-1, *turn, piece, pPositions, oPositions);
                if(checkIfOpenPoint(oPositions[arrIndexOfPiece][1] + (dice[0] + dice[1]), *turn, board, pPositions, oPositions)){
                    
                    if (arrIndexOfPiece != -1){
                        oPositions[arrIndexOfPiece][1] += (dice[0] + dice[1]);
                        tryAgain = 0;
                        (*turn) = !(*turn);
                    }else{
                        printf("Cannot find piece. Try again.\n");
                    }
                }else{
                    printf("You can't move to that point, it's occupied by an enemy piece.\n");
                }
            }else{
                printf("You can't move that piece.\n");
            }

        }while(tryAgain == 1);

    }
    return 0;

}

int differentPiece( bool * turn, int board[], int pPositions[][2], int oPositions[][2], int dice[]){
    int tryAgain = 1;
    if(*turn){
        do{
            int play;
            printf("Can you play only one number[1], one of the two numbers and not both[2], neither[3], or both[4]?  or go back[-1]?");
            scanf("%d", &play);
            if (play == - 1){return -1;}
            int piece1;
            int piece2;
            
            
            if(play == 4){ //play both
                printf("Which piece will you move with dice result of %d? ", dice[1]);
                scanf("%d", &piece2);
                if (piece2 == -1){return -1;}
                printf("Which piece will you move with dice result of %d? ", dice[0]);
                scanf("%d", &piece1);
                piece1--;
                piece2--;
                
                if (checkIfPieceIsFromPlayer(*turn, piece1, board, pPositions, oPositions) && checkIfPieceIsFromPlayer(*turn, piece2, board, pPositions, oPositions)){
                    int arrIndexOfPiece1 = getPieceToMove(-1, *turn, piece1, pPositions, oPositions);
                    int arrIndexOfPiece2 = getPieceToMove(arrIndexOfPiece1, *turn, piece2, pPositions, oPositions);
                    
                    
                    if(checkIfOpenPoint(pPositions[arrIndexOfPiece1][1] - dice[0], *turn, board, pPositions, oPositions) && checkIfOpenPoint(pPositions[arrIndexOfPiece2][1] - dice[1], *turn, board, pPositions, oPositions)){
                        
                        if (arrIndexOfPiece1 != arrIndexOfPiece2){
                            pPositions[arrIndexOfPiece1][1] -= dice[0];
                            pPositions[arrIndexOfPiece2][1] -= dice[1];
                            tryAgain = 0;
                            *turn = !(*turn);
                        }else if(arrIndexOfPiece1 == -1 && arrIndexOfPiece2 != -1){
                            printf("piece 1 cannot be found");
                        }else if(arrIndexOfPiece1 != -1 && arrIndexOfPiece2 == -1){
                            printf("piece 2 cannot be found");
                        }else{
                            printf("Both pieces cannot be found");
                        }
                    }else if(checkIfOpenPoint(pPositions[arrIndexOfPiece1][1] - dice[0], *turn, board, pPositions, oPositions) && !checkIfOpenPoint(pPositions[arrIndexOfPiece2][1] - dice[1], *turn, board, pPositions, oPositions)){
                        printf("Point %d is not open, please try again\n", pPositions[piece2][0] - dice[1]);

                    }else if(!checkIfOpenPoint(pPositions[arrIndexOfPiece1][1] - dice[0], *turn, board, pPositions, oPositions) && checkIfOpenPoint(pPositions[arrIndexOfPiece2][1] - dice[1], *turn, board, pPositions, oPositions)){
                        printf("Point %d is not open, please try again\n", pPositions[piece1][0] - dice[0]);
                    }
                    else{
                        printf("Neither point is open, please try again\n");
                    }
                }else if (checkIfPieceIsFromPlayer(*turn, piece1, board, pPositions, oPositions) && !checkIfPieceIsFromPlayer(*turn, piece2, board, pPositions, oPositions)){
                    printf("Piece %d is not yours. Try again\n", piece2);
                    
                }else if(!checkIfPieceIsFromPlayer(*turn, piece1, board, pPositions, oPositions) && checkIfPieceIsFromPlayer(*turn, piece2, board, pPositions, oPositions)){
                    printf("Piece %d is not yours. Try again\n", piece1);
                }else{
                    printf("Neither of the pieces are yours. Try again\n");
                }
            }
            else if(play == 1){ //play one one number
                printf("Will you play [1] %d or [2] %d? ", dice[0], dice[1]);
                int diceChoice;
                scanf("%d", &diceChoice);
                
                if(diceChoice == 1){
                    printf("Which piece will you move with dice result of %d? ", dice[diceChoice - 1]);
                    scanf("%d", &piece1);
                    piece1--;
                    if(checkIfPieceIsFromPlayer(*turn, piece1, board, pPositions, oPositions)){
                        int arrIndexOfPiece1 = getPieceToMove(-1, *turn, piece1, pPositions, oPositions);
                        
                        if(checkIfOpenPoint(pPositions[arrIndexOfPiece1][1] - dice[0], *turn, board, pPositions, oPositions)){
                            
                            pPositions[arrIndexOfPiece1][1] -= dice[0];
                            tryAgain = 0;
                            *turn = !(*turn);
                        }else{
                            printf("The point you are trying to move to is occupied. Try again\n");
                        }
                    }else{
                        printf("Piece %d is not yours. Try again\n", piece1);
                    }
                }else if(diceChoice == 2){
                    printf("Which piece will you move with dice result of %d? ", dice[diceChoice - 1]);
                    scanf("%d", &piece1);
                    piece1--;
                    if(checkIfPieceIsFromPlayer(*turn, piece1, board, pPositions, oPositions)){
                        int arrIndexOfPiece1 = getPieceToMove(-1, *turn, piece1, pPositions, oPositions);
                        if(checkIfOpenPoint(pPositions[arrIndexOfPiece1][1] - dice[1], *turn, board, pPositions, oPositions)){
                            
                            pPositions[arrIndexOfPiece1][1] -= dice[1];
                            tryAgain = 0;
                            *turn = !(*turn);
                        }else{
                            printf("The point you are trying to move to is occupied. Try again\n");
                        }
                    }else{
                        printf("Piece %d is not yours. Try again\n", piece2);
                    }
                }else{
                    printf("Invalid choice. Try again\n");
                }

            }else if(play == 2){ //play one of the two numbers and not both
                int diceChoice = (dice[0] > dice[1] ? dice[0] : (dice[0] == dice[1] ? dice[0] : dice[1])); 
                //check if dice[0] is greater than dice [1], if it is, set diceChoice to dice[0], if not, check if they are equal, if they are, set diceChoice to dice[0], if not, set diceChoice to dice[1]
                printf("Which piece will you move with dice result of %d? ", diceChoice);
                scanf("%d", &piece1);
                piece1--;
                if(checkIfPieceIsFromPlayer(*turn, piece1, board, pPositions, oPositions)){
                    int arrIndexOfPiece1 = getPieceToMove(-1, *turn, piece1, pPositions, oPositions);
                    
                    if(checkIfOpenPoint(pPositions[arrIndexOfPiece1][1] - diceChoice, *turn, board, pPositions, oPositions)){
                        
                        pPositions[arrIndexOfPiece1][1] -= diceChoice;
                        tryAgain = 0;
                        *turn = !(*turn);
                    }else{
                        printf("The point you are trying to move to is occupied. Try again\n");
                    }
                }else{
                    printf("Piece %d is not yours. Try again\n", piece1);
                }
                
            }else if (play == 3){
                printf("You have forfeited your turn.\n");
                tryAgain = 0;
                *turn = !(*turn);
            }
                

        }while(tryAgain == 1);
    }else{
        do{
            int play;
            printf("Can you play only one number[1], one of the two numbers and not both[2], neither[3], or both[4]?  ");
            scanf("%d", &play);
            int piece1;
            int piece2;
            
            
            if(play == 4){ //play both
                printf("Which piece will you move with dice result of %d? ", dice[1]);
                scanf("%d", &piece2);
                printf("Which piece will you move with dice result of %d? ", dice[0]);
                scanf("%d", &piece1);
                
                piece1--;
                piece2--;
                if (checkIfPieceIsFromPlayer(*turn, piece1, board, pPositions, oPositions) && checkIfPieceIsFromPlayer(*turn, piece2, board, pPositions, oPositions)){
                    int arrIndexOfPiece1 = getPieceToMove(-1, *turn, piece1, pPositions, oPositions);
                    int arrIndexOfPiece2 = getPieceToMove(arrIndexOfPiece1, *turn, piece2, pPositions, oPositions);
                    
                    if(checkIfOpenPoint(oPositions[arrIndexOfPiece1][1] + dice[0], *turn, board, pPositions, oPositions) && checkIfOpenPoint(oPositions[arrIndexOfPiece2][1] + dice[1], *turn, board, pPositions, oPositions)){
                        
                        if (arrIndexOfPiece1 != arrIndexOfPiece2){
                            oPositions[arrIndexOfPiece1][1] += dice[0];
                            oPositions[arrIndexOfPiece2][1] += dice[1];
                            tryAgain = 0;
                            *turn = !(*turn);
                        }else if(arrIndexOfPiece1 == -1 && arrIndexOfPiece2 != -1){
                            printf("piece 1 cannot be found");
                        }else if(arrIndexOfPiece1 != -1 && arrIndexOfPiece2 == -1){
                            printf("piece 2 cannot be found");
                        }else{
                            printf("Both pieces cannot be found");
                        }
                    }else if(checkIfOpenPoint(oPositions[arrIndexOfPiece1][1] + dice[0], *turn, board, pPositions, oPositions) && !checkIfOpenPoint(oPositions[arrIndexOfPiece2][1] + dice[1], *turn, board, pPositions, oPositions)){
                        printf("Point %d is occupied. Try again\n", oPositions[piece2][0] + dice[1]);

                    }else if(!checkIfOpenPoint(oPositions[arrIndexOfPiece1][1] + dice[0], *turn, board, pPositions, oPositions) && checkIfOpenPoint(oPositions[arrIndexOfPiece2][1] + dice[1], *turn, board, pPositions, oPositions)){
                        printf("Point %d is occupied. Try again\n", oPositions[piece1][0] + dice[0]);
                    }
                    else{
                        printf("One of the points you are trying to move to is occupied. Try again\n");
                    }
                }else if (checkIfPieceIsFromPlayer(*turn, piece1, board, pPositions, oPositions) && !checkIfPieceIsFromPlayer(*turn, piece2, board, pPositions, oPositions)){
                    printf("Piece %d is not yours. Try again\n", piece2);
                    
                }else if(!checkIfPieceIsFromPlayer(*turn, piece1, board, pPositions, oPositions) && checkIfPieceIsFromPlayer(*turn, piece2, board, pPositions, oPositions)){
                    printf("Piece %d is not yours. Try again\n", piece1);
                }else{
                    printf("Neither of the pieces are yours. Try again\n");
                }
            }
            else if(play == 1){ //play one one number
                printf("Will you play [1] %d or [2] %d? ", dice[0], dice[1]);
                int diceChoice;
                scanf("%d", &diceChoice);
                
                if(diceChoice == 1){
                    printf("Which piece will you move with dice result of %d? ", dice[diceChoice - 1]);
                    scanf("%d", &piece1);
                    piece1--;
                    if(checkIfPieceIsFromPlayer(*turn, piece1, board, pPositions, oPositions)){
                        int arrIndexOfPiece1 = getPieceToMove(-1, *turn, piece1, pPositions, oPositions);
                        
                        if(checkIfOpenPoint(oPositions[arrIndexOfPiece1][1] + dice[0], *turn, board, pPositions, oPositions)){
                            
                            oPositions[arrIndexOfPiece1][1] += dice[0];
                            tryAgain = 0;
                            *turn = !(*turn);
                        }else{
                            printf("The point you are trying to move to is occupied. Try again\n");
                        }
                    }else{
                        printf("Piece %d is not yours. Try again\n", piece1);
                    }
                }else if(diceChoice == 2){
                    printf("Which piece will you move with dice result of %d? ", dice[diceChoice - 1]);
                    scanf("%d", &piece1);
                    piece1--;
                    if(checkIfPieceIsFromPlayer(*turn, piece1, board, pPositions, oPositions)){
                        int arrIndexOfPiece1 = getPieceToMove(-1, *turn, piece1, pPositions, oPositions);
                        
                        if(checkIfOpenPoint(oPositions[arrIndexOfPiece1][1] + dice[1], *turn, board, pPositions, oPositions)){
                            
                            oPositions[arrIndexOfPiece1][1] += dice[1];
                            tryAgain = 0;
                            *turn = !(*turn);
                        }else{
                            printf("The point you are trying to move to is occupied. Try again\n");
                        }
                    }else{
                        printf("Piece %d is not yours. Try again\n", piece2);
                    }
                }else{
                    printf("Invalid choice. Try again\n");
                }

            }else if(play == 2){ //play one of the two numbers and not both
                int diceChoice = (dice[0] > dice[1] ? dice[0] : (dice[0] == dice[1] ? dice[0] : dice[1])); 
                //check if dice[0] is greater than dice [1], if it is, set diceChoice to dice[0], if not, check if they are equal, if they are, set diceChoice to dice[0], if not, set diceChoice to dice[1]
                printf("Which piece will you move with dice result of %d? ", diceChoice);
                scanf("%d", &piece1);
                piece1--;
                if(checkIfPieceIsFromPlayer(*turn, piece1, board, pPositions, oPositions)){
                    int arrIndexOfPiece1 = getPieceToMove(-1, *turn, piece1, pPositions, oPositions);
                    
                    if(checkIfOpenPoint(oPositions[arrIndexOfPiece1][1] + diceChoice, *turn, board, pPositions, oPositions)){
                       
                        oPositions[arrIndexOfPiece1][1] += diceChoice;
                        tryAgain = 0;
                        *turn = !(*turn);
                    }else{
                        printf("The point you are trying to move to is occupied. Try again\n");
                    }
                }else{
                    printf("Piece %d is not yours. Try again\n", piece1);
                }
                
            }else if (play == 3){
                printf("You have forfeited your turn.\n");
                tryAgain = 0;
                *turn = !(*turn);
            }
                

        }while(tryAgain == 1);

    }
    return 0;

}

void makeMove(bool * turn, int board[], int pPositions[][2], int oPositions[][2], int dice[]){
    
    
    if (dice[0] == dice[1]){
        printf("You rolled the same number twice. Will you choose to move a piece 4 times the dice number?[y]/[n]\n");
        char choice;
        scanf(" %c", &choice);
        if(choice == 'y'){
            equalDiceResult(turn, board, pPositions, oPositions, dice);
        }else{
            printf("[1]Will you move one piece twice the dice number? or [2]two pieces for both numbers?\n");
            int numChoice;
            scanf("%d", &numChoice);
            if (numChoice == 1){
                samePieceBothResults(turn, board, pPositions, oPositions, dice);
            }else{
                differentPiece(turn, board, pPositions, oPositions, dice);
            }
        }
    
    }else{
        printf("[1]Will you move one piece twice the dice number? or [2]two pieces for both numbers?\n");
        int numChoice;
        scanf("%d", &numChoice);
        if (numChoice == 1){
            samePieceBothResults(turn, board, pPositions, oPositions, dice);
        }else{
            differentPiece(turn, board, pPositions, oPositions, dice);
        }

    }
    
    
}
bool checkBar(int bar[30][2], bool turn){
    if (turn){
        for (int i = 0;i < 30;i++){
            if (bar[i][0] != -99){
                return true;
            }
        }
        return false;
    }else{
        for (int i = 0;i < 30;i++){
            if (bar[i][1] != -99){
                return true;
            }
        }
        return false;
    }
}

bool barIsEmpty(bool turn, int oPositions[2], int pPositions[][2], int bar[30][2]){
    if (checkBar(bar, turn)){
        if(turn){
            char rollDice;
            printf("You have a piece on the bar, you must roll a dice first.\n");
            scanf(" %c", &rollDice);
            int nDice = singleDiceRoll();
            

        }

    }
}
    
