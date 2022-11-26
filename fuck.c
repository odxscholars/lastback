#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<time.h>
#define EMPTY -50
#define INBAR -100
#define BEAREDOFF -200
//SENTINEL VALUES
/*
Empty - "-50"
inBar - "-100"
bearedOff - "-200"
*/
typedef struct checker{
    bool isPlayerPiece;
    int position;
    bool bearedOff;
    bool inBar;
    bool isEmpty;
}checker;

typedef struct pip{
    int numCheckers;
    checker checkersInPip[15];
} pip;


typedef struct quadrant{
    pip pips[6];
} quadrant;


typedef struct board{
    quadrant quadrants[4];
    bool player1turn;
    int barCount;
    checker playerBar[30];
} board;


int singularDiceRoll(){
    int diceRoll = rand() % 6 + 1;
    return diceRoll;

}

void doubleDiceRoll(int dice[]){
    dice[0] = singularDiceRoll();
    dice[1] = singularDiceRoll();
    
}


void initializeBoard(board *gameBoard){
    gameBoard->barCount = 0;
    int pPositions[4] = {23,12,7,5};
    int oPositions[4] = {0, 11, 16, 18};
    int initQty[4] = {2, 5, 3, 5};
    int count = 0;
    //set everything to zero
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 6; j++){
            gameBoard->quadrants[i].pips[j].numCheckers = 0;
        }
    }
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 6; j++){
            for(int k = 0; k < 15; k++){
                gameBoard->quadrants[i].pips[j].checkersInPip[k].position = EMPTY;
                gameBoard->quadrants[i].pips[j].checkersInPip[k].isEmpty = true;
                gameBoard->quadrants[i].pips[j].checkersInPip[k].inBar = false;
                gameBoard->quadrants[i].pips[j].checkersInPip[k].bearedOff = false;
            }
        }
    }
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < initQty[i]; j++){
            int q1 = pPositions[i] / 6;
            int q2 = oPositions[i] / 6;
            int p1 = pPositions[i] % 6;
            int p2 = oPositions[i] % 6;
            gameBoard->quadrants[q1].pips[p1].checkersInPip[j].isPlayerPiece = true;
            gameBoard->quadrants[q1].pips[p1].checkersInPip[j].position = pPositions[i];
            gameBoard->quadrants[q1].pips[p1].checkersInPip[j].bearedOff = false;
            gameBoard->quadrants[q1].pips[p1].checkersInPip[j].inBar = false;
            gameBoard->quadrants[q2].pips[p2].checkersInPip[j].isPlayerPiece = false;
            gameBoard->quadrants[q2].pips[p2].checkersInPip[j].position = oPositions[i];
            gameBoard->quadrants[q2].pips[p2].checkersInPip[j].bearedOff = false;
            gameBoard->quadrants[q2].pips[p2].checkersInPip[j].inBar = false;
            gameBoard->quadrants[q1].pips[p1].numCheckers++;
            gameBoard->quadrants[q2].pips[p2].numCheckers++;
            gameBoard->quadrants[q1].pips[p1].checkersInPip[j].isEmpty = false;
            gameBoard->quadrants[q2].pips[p2].checkersInPip[j].isEmpty = false;

        }
    }
    //print all checkers and their info
    

}


int getMaxBetweenTwoQuadrants(quadrant a, quadrant b){
    int max = 0;
    for(int i = 0; i < 6; i++){
        if(a.pips[i].numCheckers > max){
            max = a.pips[i].numCheckers;
        }
        if(b.pips[i].numCheckers > max){
            max = b.pips[i].numCheckers;
        }
    }
    return max;

}
void changeTurn(board *gameBoard){
    gameBoard->player1turn = !gameBoard->player1turn;

}
void displayGame(board * gameBoard){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 6; j++){
            for(int k = 0; k < gameBoard->quadrants[i].pips[j].numCheckers; k++){
                printf("\nChecker %d: isPlayerPiece: %d, position: %d, bearedOff: %d, inBar: %d, isEmpty: %s, q: %d, p: %d", k, gameBoard->quadrants[i].pips[j].checkersInPip[k].isPlayerPiece, gameBoard->quadrants[i].pips[j].checkersInPip[k].position, gameBoard->quadrants[i].pips[j].checkersInPip[k].bearedOff, gameBoard->quadrants[i].pips[j].checkersInPip[k].inBar, gameBoard->quadrants[i].pips[j].checkersInPip[k].isEmpty ? "true" : "false", i, j);
            }
        }
    }
    printf("\n");
    for(int i = 12; i < 24; i++ ){
        printf(" %d ", i);
    }
    printf("\n");
    for(int i = 0; i < getMaxBetweenTwoQuadrants(gameBoard->quadrants[2], gameBoard->quadrants[3]); i++){
        for(int j = 12; j < 24; j++){
            int q = j / 6;
            int p = j % 6;
            if(gameBoard->quadrants[q].pips[p].numCheckers > i){
                printf(" %s ", gameBoard->quadrants[q].pips[p].checkersInPip[i].isPlayerPiece ? "<>" : "--");
            }
            else{
                printf("    ");
            }
        }
        printf("\n");
    }
    
    printf("---------------------------------------------------\n");
    for(int i = 11; i >= 0; i--){
        if (i < 10){
            printf(" 0%d ", i);
        }else{
            printf(" %d ", i);
        }
    }
    printf("\n");
    for(int i = 0; i < getMaxBetweenTwoQuadrants(gameBoard->quadrants[1], gameBoard->quadrants[0]); i++){
        for(int j = 11; j >= 0; j--){
            int q = j / 6;
            int p = j % 6;
            if(gameBoard->quadrants[q].pips[p].numCheckers > i){
                printf(" %s ", gameBoard->quadrants[q].pips[p].checkersInPip[i].isPlayerPiece ? "<>" : "--");
            }
            else{
                printf("    ");
            }
        }
        printf("\n");
    }
    printf("\n");

}

int checkIfPipIsOpen(int finalpos, board *gameBoard){
    int count = 0;
    if (gameBoard->player1turn == true){
        
        int q = finalpos / 6;
        int p = finalpos % 6;
        printf("q: %d, p: %d, numCheckers: %d\n", q, p, gameBoard->quadrants[q].pips[p].numCheckers);
        if (gameBoard->quadrants[q].pips[p].numCheckers == 0){
            return 0;
        }
        else{
            for(int i = 0; i < gameBoard->quadrants[q].pips[p].numCheckers; i++){
                if(gameBoard->quadrants[q].pips[p].checkersInPip[i].isPlayerPiece == false){
                    count++;
                }
            }

        }
        return count;
    }else{
        int q = finalpos / 6;
        int p = finalpos % 6;
        if (gameBoard->quadrants[q].pips[p].numCheckers == 0){
            printf("returned count");
            return count;
        }
        else{
            for(int i = 0; i < gameBoard->quadrants[q].pips[p].numCheckers; i++){
                if(gameBoard->quadrants[q].pips[p].checkersInPip[i].isPlayerPiece == true){
                    count++;
                }
            }

        }
        return count;
    }
    return count;


}
int checkIfPlayerHasPieceInPip(int indexToIgnore, int pos, board *gameBoard){
    if (gameBoard->player1turn== true){
        
        int q = pos / 6;
        int p = pos % 6;

        printf("check pos: %d q: %d, p: %d\n", pos, q, p);
        for(int i = gameBoard->quadrants[q].pips[p].numCheckers; i >= 0; i--){
            if(gameBoard->quadrants[q].pips[p].checkersInPip[i].isPlayerPiece == true && gameBoard->quadrants[q].pips[p].checkersInPip[i].bearedOff == false && gameBoard->quadrants[q].pips[p].checkersInPip[i].inBar == false && gameBoard->quadrants[q].pips[p].checkersInPip[i].isEmpty == false && i != indexToIgnore){
                return i;
            }
        }
        return -1;
    }else{
        int q = pos / 6;
        int p = pos % 6;
        for(int i = gameBoard->quadrants[q].pips[p].numCheckers; i >= 0; i--){
            if(gameBoard->quadrants[q].pips[p].checkersInPip[i].isPlayerPiece == false && gameBoard->quadrants[q].pips[p].checkersInPip[i].bearedOff == false && gameBoard->quadrants[q].pips[p].checkersInPip[i].inBar == false && gameBoard->quadrants[q].pips[p].checkersInPip[i].isEmpty != true && i != indexToIgnore){
                return i;
            }
        }
        return -1;
    }
}
void setPieceToEmpty(int checkerIndex, int pos, board *gameBoard){
    int q = pos / 6;
    int p = pos % 6;
    gameBoard->quadrants[q].pips[p].checkersInPip[checkerIndex].isEmpty = true;
    gameBoard->quadrants[q].pips[p].checkersInPip[checkerIndex].isPlayerPiece = false;
    gameBoard->quadrants[q].pips[p].checkersInPip[checkerIndex].inBar = false;
    gameBoard->quadrants[q].pips[p].checkersInPip[checkerIndex].bearedOff = false;
    gameBoard->quadrants[q].pips[p].numCheckers--;



}

void setPieceToFilled(int pos, board *gameBoard){
    if (gameBoard->player1turn == true){
        int q = pos / 6;
        int p = pos % 6;
        int emptyPos = -1;
        for(int i = 0; i < 15;i++){
            if(gameBoard->quadrants[q].pips[p].checkersInPip[i].isEmpty == true){
                emptyPos = i;
                i = 15;
            }
        }
        if(emptyPos != -1){
            gameBoard->quadrants[q].pips[p].checkersInPip[emptyPos].position = pos;
            gameBoard->quadrants[q].pips[p].checkersInPip[emptyPos].isEmpty = false;
            gameBoard->quadrants[q].pips[p].checkersInPip[emptyPos].isPlayerPiece = true;
            gameBoard->quadrants[q].pips[p].checkersInPip[emptyPos].inBar = false;
            gameBoard->quadrants[q].pips[p].checkersInPip[emptyPos].bearedOff = false;
            gameBoard->quadrants[q].pips[p].numCheckers++;

        }else{
            printf("Error: No empty space in pip\n");
        }
    }else{
        int q = pos / 6;
        int p = pos % 6;
        int emptyPos = -1;
        for(int i = 0; i < 15;i++){
            if(gameBoard->quadrants[q].pips[p].checkersInPip[i].isEmpty == true){
                emptyPos = i;
                i = 15;
            }
        }
        if(emptyPos != -1){
            gameBoard->quadrants[q].pips[p].checkersInPip[emptyPos].position = pos;
            gameBoard->quadrants[q].pips[p].checkersInPip[emptyPos].isEmpty = false;
            gameBoard->quadrants[q].pips[p].checkersInPip[emptyPos].isPlayerPiece = false;
            gameBoard->quadrants[q].pips[p].checkersInPip[emptyPos].inBar = false;
            gameBoard->quadrants[q].pips[p].checkersInPip[emptyPos].bearedOff = false;
            gameBoard->quadrants[q].pips[p].numCheckers++;

        }else{
            printf("Error: No empty space in pip\n");
        }
    }
}
int getOpponentPiece(int posToGet, board *gameBoard){
    if (gameBoard->player1turn == true){
        int q = posToGet / 6;
        int p = posToGet % 6;
        for(int i = gameBoard->quadrants[q].pips[p].numCheckers; i >= 0; i--){
            if(gameBoard->quadrants[q].pips[p].checkersInPip[i].isPlayerPiece == false && gameBoard->quadrants[q].pips[p].checkersInPip[i].bearedOff == false && gameBoard->quadrants[q].pips[p].checkersInPip[i].inBar == false && gameBoard->quadrants[q].pips[p].checkersInPip[i].isEmpty == false){
                return i;
            }
        }
        return -1;
    }else{
        int q = posToGet / 6;
        int p = posToGet % 6;
        for(int i = gameBoard->quadrants[q].pips[p].numCheckers; i >= 0; i--){
            if(gameBoard->quadrants[q].pips[p].checkersInPip[i].isPlayerPiece == true && gameBoard->quadrants[q].pips[p].checkersInPip[i].bearedOff == false && gameBoard->quadrants[q].pips[p].checkersInPip[i].inBar == false && gameBoard->quadrants[q].pips[p].checkersInPip[i].isEmpty == false){
                return i;
            }
        }
        return -1;
    }

}
void addPieceToBar(int finalPos, int indexOfOpp, board *gameBoard){
    if(gameBoard->player1turn == true){
        int q = finalPos / 6;
        int p = finalPos % 6;
        gameBoard->playerBar[gameBoard->barCount] = gameBoard->quadrants[q].pips[p].checkersInPip[indexOfOpp];
        gameBoard->playerBar[gameBoard->barCount].position = INBAR;
        gameBoard->playerBar[gameBoard->barCount].inBar = true;
        gameBoard->playerBar[gameBoard->barCount].isEmpty = false;
        gameBoard->barCount++;
        
    }

}
void blotPiece(int finalPos, int oldPos, board *gameBoard){
    if (gameBoard->player1turn == true){
        if (checkIfPipIsOpen(finalPos, gameBoard) == 1){
            int index = checkIfPlayerHasPieceInPip(-1, oldPos, gameBoard);
            int indexOfOpp = getOpponentPiece(finalPos, gameBoard);
            addPieceToBar(finalPos, indexOfOpp, gameBoard);
            setPieceToEmpty(indexOfOpp, finalPos, gameBoard);
            setPieceToEmpty(index, oldPos, gameBoard);
            setPieceToFilled(finalPos, gameBoard);

        }
    }

}
void movePiece(int amtToMove, int oldPos, board *gameBoard){
    
    if (gameBoard->player1turn == true){
        int finalPos = oldPos - amtToMove;
        if (checkIfPlayerHasPieceInPip(-1, oldPos, gameBoard) != -1){
            if (checkIfPipIsOpen(oldPos - amtToMove, gameBoard) == 0){
                printf("editing pieces\n");
                printf("finalPos: %d\n", finalPos);
                printf("oldPos: %d\n", oldPos);
                int q = oldPos / 6;
                int p = oldPos % 6;
                int q2 = (finalPos) / 6;
                int p2 = (finalPos) % 6;
                int checker = checkIfPlayerHasPieceInPip(-1, oldPos, gameBoard);
                
                setPieceToEmpty(checker, oldPos, gameBoard);
                setPieceToFilled(finalPos, gameBoard);
                
            }else if(checkIfPipIsOpen(oldPos - amtToMove, gameBoard) == 1){
                blotPiece(finalPos, oldPos, gameBoard);
            }
            else{
                printf("This pip is not open\n");
            }
        }else{
            printf("Player has no piece here\n");
        }
    }else{
        int finalPos = oldPos + amtToMove;
        printf("finalPos: %d\n", finalPos);
        if (checkIfPlayerHasPieceInPip(-1, oldPos, gameBoard) != -1){
            if (checkIfPipIsOpen(finalPos, gameBoard) == 0){
                printf("editing pieces\n");
                printf("finalPos: %d\n", finalPos);
                printf("oldPos: %d\n", oldPos);
                int q = oldPos / 6;
                int p = oldPos % 6;
                int q2 = (finalPos) / 6;
                int p2 = (finalPos) % 6;
                int checker = checkIfPlayerHasPieceInPip(-1, oldPos, gameBoard);
                
                setPieceToEmpty(checker, oldPos, gameBoard);
                setPieceToFilled(finalPos, gameBoard);
            }else{
                printf("This pip is not open\n");
            }
        }else{
            printf("Cannot find piece\n");
        }
    }


}

void moveTwoPieces(board *gameBoard, int dice[2]){
    int piece1;
    int piece2;
    int choice;
    printf("Can you move two pieces? 1 for yes, 2 for no\n");
    scanf("%d", &choice);
    if (choice == 1){
        printf("Which piece will you move with %d positions\n", dice[0]);
        scanf("%d", &piece1);
        printf("Which piece will you move with %d positions\n", dice[1]);
        scanf("%d", &piece2);
        int checkResult1 = checkIfPlayerHasPieceInPip(-1, piece1, gameBoard);
        int checkResult2 = checkIfPlayerHasPieceInPip(checkResult1, piece2, gameBoard);
        if (checkResult1 != -1 && checkResult2 != -1){
            movePiece(dice[0], piece1, gameBoard);
            movePiece(dice[1], piece2, gameBoard);
        }

    }else{

    }
    


}

void moveOnePieceFourTimes(board *gameBoard, int dice[2]){
    int piecePosition;
    printf("What is the position of the piece that you want to move? ");
    scanf("%d", &piecePosition);
    if(gameBoard->player1turn == true){
        for(int i = 4; i >= 1; i--){
            if (checkIfPipIsOpen(dice[0] * i, gameBoard) == 0){
                printf("You are able to move %d positions\n", dice[0] * i);
                movePiece(dice[0] * 4, piecePosition, gameBoard);
                i = 0;

            }
        }
    }else{
        for(int i = 4; i >= 1; i--){
            if (checkIfPipIsOpen(dice[0] * i, gameBoard) == 0){
                printf("You are able to move %d positions\n", dice[0] * i);
                movePiece(dice[0] * 4, piecePosition, gameBoard);
                i = 0;

            }
        }

    }
    


}
int barPromptIfTrue(board *gameBoard){
    if(gameBoard->barCount != 0){
        if (gameBoard->player1turn == true){
            for(int i = 0; i < gameBoard->barCount; i++){
                if (gameBoard->playerBar[i].isPlayerPiece == true){
                    return i;
                }
            }
        }else{
            for(int i = 0; i < gameBoard->barCount; i++){
                if (gameBoard->playerBar[i].isPlayerPiece == false){
                    return i;
                }
            }
        }
    }else{
        return -1;
    }
    return -1;

}


void shiftBar(int indexToRemove, board *gameBoard){
    for(int i = indexToRemove; i < gameBoard->barCount; i++){
        gameBoard->playerBar[i] = gameBoard->playerBar[i + 1];
    }
    gameBoard->barCount--;
}

void gameChoice(board *gameBoard, int dice[2]){
    printf("barPrompt result: %d\n", barPromptIfTrue(gameBoard));
    if (barPromptIfTrue(gameBoard) != -1){
        char temp;
        printf("Player %s, you have a checker in the bar\n", gameBoard->player1turn ? "1" : "2");
        printf("You must roll the dice to reinstate it back in the board\n"); 
        scanf(" %c", &temp);
        int result = singularDiceRoll();
        if (gameBoard->player1turn==true){
            if(checkIfPipIsOpen(17 + result, gameBoard) == 0){
                int indexToRemove = barPromptIfTrue(gameBoard);
                printf("You are able to move %d positions\n", result);
                setPieceToFilled(17 + result, gameBoard);
                shiftBar(indexToRemove, gameBoard);

                

            }else{
                printf("You are not able to move %d positions\n", result);
            }

        }else{
            if(checkIfPipIsOpen(result - 1, gameBoard) == 0){
                int indexToRemove = barPromptIfTrue(gameBoard);
                printf("You are able to move %d positions\n", result);
                setPieceToFilled(result - 1, gameBoard);
                shiftBar(indexToRemove, gameBoard);
            }else{
                printf("You are not able to move %d positions\n", result);
            }
        }

        

    }else{
        printf("[1] Move one piece\n");
        printf("[2] Move two pieces\n");
        if (dice[0] == dice[1]){
            printf("[3] Move one piece four times\n");
        }
        int choice;
        scanf("%d", &choice);
        if (choice == 1){
            int piecePositionToMove;
            bool keepGoing = true;
            do{
                printf("Enter the position of the piece you want to move\n");
                scanf("%d", &piecePositionToMove);
                if (checkIfPlayerHasPieceInPip(-1, piecePositionToMove, gameBoard) == -1){
                    printf("You do not have a piece here\n");
                    
                }else{
                    movePiece(dice[0] + dice[1], piecePositionToMove, gameBoard);
                    keepGoing = false;
                }

            }while(keepGoing);

        }else if(choice == 2){
            moveTwoPieces(gameBoard, dice);
        }else if(choice == 3 && dice[0] == dice[1]){
            moveOnePieceFourTimes(gameBoard, dice);
        }else if(choice == 3 && dice[0] != dice[1]){
            printf("You cannot move one piece four times. You can only do that if dice results are equal\n");
        }
    }

}

void printBar(board *gameBoard){
    printf("BAR: \n");
    for(int i = 0; i < gameBoard->barCount; i++){
        printf("Player %d\n", gameBoard->playerBar[i].isPlayerPiece ? 1 : 2);
    }

}
void driver(board* gameBoard){
    int dice[2];
    bool continuePlaying = true;
    gameBoard->player1turn = true;
    initializeBoard(gameBoard);
    
    do{
        displayGame(gameBoard);
        printBar(gameBoard);
        printf("Player %s's turn\n", gameBoard->player1turn ? "1" : "2");

        printf("Dice[0]: ");
        scanf("%d", &dice[0]);
        printf("Dice[1]: ");
        scanf("%d", &dice[1]);
        gameChoice(gameBoard, dice);
        changeTurn(gameBoard);


    }while(continuePlaying == true);

}


int main(){
    board gameBoard;
    driver(&gameBoard);
    return 0;


}