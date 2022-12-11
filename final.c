/*
    Name:
    Section:
    Date:
    Description:
*/


#include<stdio.h> // include the standard input/output library
#include<stdlib.h> // include the standard library
#include<stdbool.h> // include the standard boolean library
#include<time.h> // include the time library
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
    bool isPlayerPiece; //true if player, false if opponent
    int position; //position on board
    bool bearedOff; //true if beared off, false if not
    bool inBar; //true if in bar, false if not
    bool isEmpty; //true if empty, false if not
}checker; //checker struct

typedef struct pip{
    int numCheckers; // number of checkers on pip
    checker checkersInPip[15]; //array of checkers in pip
} pip;


typedef struct quadrant{
    pip pips[6];//array of pips in quadrant
} quadrant;


typedef struct board{
    quadrant quadrants[4]; //array of quadrants on board
    bool player1turn;//true if player 1's turn, false if player 2's turn
    int barCount; //number of checkers in bar
    checker playerBar[30]; //array of checkers in player's bar
    int player1BearedOff; //number of checkers beared off for player 1
    int player2BearedOff; //number of checkers beared off for player 2
    int stake; //stake of game
    bool player1OwnerStake; //true if player1 owns stake
} board;


/*
    This function rolls a singular dice and returns the value
    @param none
    @return int - value of dice roll
    
*/
int singularDiceRoll(){
    
    int diceRoll = rand() % 6 + 1;
    return diceRoll;

}

void doubleDiceRoll(int dice[]){
    /*
    This function rolls two dice and returns the values in an array
    @param int dice[] - array to store dice values
    @return void
    */
    dice[0] = singularDiceRoll();
    dice[1] = singularDiceRoll();
    
}


void initializeBoard(board *gameBoard){
    /*
    This function initializes the board
    @param board *gameBoard - pointer to board struct
    @return void
    */
    gameBoard->stake = 64;
    gameBoard->barCount = 0;
    int pPositions[4] = {23,12,7,5};
    int oPositions[4] = {0, 11, 16, 18};
    int initQty[4] = {2, 5, 3, 5};
    
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
    gameBoard->player1BearedOff = 0;
    gameBoard->player2BearedOff = 0;
    //print all checkers and their info
    

}


int getMaxBetweenTwoQuadrants(quadrant a, quadrant b){
    /*
    This function returns the maximum number of checkers between two quadrants
    @param quadrant a - first quadrant
    @param quadrant b - second quadrant
    @return int - maximum number of checkers between two quadrants
    */
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
    /*
    This function changes the turn
    @param board *gameBoard - pointer to board struct
    @return void
    */

    gameBoard->player1turn = !gameBoard->player1turn;

}
void displayGame(board * gameBoard){
    /*
    This function displays the game
    @param board *gameBoard - pointer to board struct
    @return void
    */
    // for(int i = 0; i < 4; i++){
    //     for(int j = 0; j < 6; j++){
    //         for(int k = 0; k < gameBoard->quadrants[i].pips[j].numCheckers; k++){
    //             printf("\nChecker %d: isPlayerPiece: %d, position: %d, bearedOff: %d, inBar: %d, isEmpty: %s, q: %d, p: %d", k, gameBoard->quadrants[i].pips[j].checkersInPip[k].isPlayerPiece, gameBoard->quadrants[i].pips[j].checkersInPip[k].position, gameBoard->quadrants[i].pips[j].checkersInPip[k].bearedOff, gameBoard->quadrants[i].pips[j].checkersInPip[k].inBar, gameBoard->quadrants[i].pips[j].checkersInPip[k].isEmpty ? "true" : "false", i, j);
    //         }
    //     }
    // }
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
    /*
    This function checks if a pip is open
    @param int finalpos - final position of checker
    @param board *gameBoard - pointer to board struct
    @return int - 1 if pip is open, 0 and positive numbers if not
    */
    int count = 0;
    if (finalpos >= 0 && finalpos < 24){
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
    }else{
        printf("This move is deemed out of bounds.\n");
        return -1;
    }
    return count;


}
int checkIfPlayerHasPieceInPip(int indexToIgnore, int pos, board *gameBoard){
    /*
    This function checks if a player has a piece in a pip
    @param int indexToIgnore - index of checker to ignore
    @param int pos - position of pip
    @param board *gameBoard - pointer to board struct
    @return int - the index of the piece if player has piece in pip, -1 if not
    */
   if (pos >= 0 && pos < 24){
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

   }else {
        printf("This move is deemed out of bounds.\n");
        return -1;
   }
    
}
void setPieceToEmpty(int checkerIndex, int pos, board *gameBoard){
    /*
    This function sets a piece to empty
    @param int checkerIndex - index of checker to set to empty
    @param int pos - position of pip
    @param board *gameBoard - pointer to board struct
    */

    int q = pos / 6;
    int p = pos % 6;
    gameBoard->quadrants[q].pips[p].checkersInPip[checkerIndex].isEmpty = true;
    gameBoard->quadrants[q].pips[p].checkersInPip[checkerIndex].isPlayerPiece = false;
    gameBoard->quadrants[q].pips[p].checkersInPip[checkerIndex].inBar = false;
    gameBoard->quadrants[q].pips[p].checkersInPip[checkerIndex].bearedOff = false;
    gameBoard->quadrants[q].pips[p].numCheckers--;



}
void setPieceToBearedOff(int checkerIndex, int pos, board *gameBoard){
    /*
    This function sets a piece to beared off
    @param int checkerIndex - index of checker to set to beared off
    @param int pos - position of pip
    @param board *gameBoard - pointer to board struct
    */

    int q = pos / 6;
    int p = pos % 6;
    gameBoard->quadrants[q].pips[p].checkersInPip[checkerIndex].isEmpty = true;
    gameBoard->quadrants[q].pips[p].checkersInPip[checkerIndex].isPlayerPiece = false;
    gameBoard->quadrants[q].pips[p].checkersInPip[checkerIndex].inBar = false;
    gameBoard->quadrants[q].pips[p].checkersInPip[checkerIndex].bearedOff = true;
    gameBoard->quadrants[q].pips[p].numCheckers--;
    if (gameBoard->player1turn){
        gameBoard->player1BearedOff++;
    }else{
        gameBoard->player1BearedOff++;
    }

}
void setPieceToFilled(int pos, board *gameBoard){
    /*
    This function sets a piece to filled
    @param int pos - position of pip
    @param board *gameBoard - pointer to board struct
    */

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
    /*
    This function gets the index of the opponent piece in a pip
    @param int posToGet - position of pip to get
    @param board *gameBoard - pointer to board struct
    @return int - index of opponent piece
    */

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
    /*
    This function adds a piece to the bar
    @param int finalPos - position of pip
    @param int indexOfOpp - index of opponent piece
    @param board *gameBoard - pointer to board struct
    */

    if(gameBoard->player1turn == true){
        int q = finalPos / 6;
        int p = finalPos % 6;
        gameBoard->playerBar[gameBoard->barCount] = gameBoard->quadrants[q].pips[p].checkersInPip[indexOfOpp];
        gameBoard->playerBar[gameBoard->barCount].position = INBAR;
        gameBoard->playerBar[gameBoard->barCount].inBar = true;
        gameBoard->playerBar[gameBoard->barCount].isEmpty = false;
        gameBoard->barCount++;
        
    }else{
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
    /*
    This function blots a piece
    @param int finalPos - position of pip
    @param int oldPos - position of pip
    @param board *gameBoard - pointer to board struct
    */

    if (gameBoard->player1turn == true){
        if (checkIfPipIsOpen(finalPos, gameBoard) == 1){
            int index = checkIfPlayerHasPieceInPip(-1, oldPos, gameBoard);
            int indexOfOpp = getOpponentPiece(finalPos, gameBoard);
            addPieceToBar(finalPos, indexOfOpp, gameBoard);
            setPieceToEmpty(indexOfOpp, finalPos, gameBoard);
            setPieceToEmpty(index, oldPos, gameBoard);
            setPieceToFilled(finalPos, gameBoard);

        }
    }else{
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
    /*
    This function moves a piece
    @param int amtToMove - amount to move
    @param int oldPos - position of pip
    @param board *gameBoard - pointer to board struct
    
    */
    if (gameBoard->player1turn == true){
        int finalPos = oldPos - amtToMove;
        if (checkIfPlayerHasPieceInPip(-1, oldPos, gameBoard) != -1){
            if (checkIfPipIsOpen(oldPos - amtToMove, gameBoard) == 0){
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
                
                int checker = checkIfPlayerHasPieceInPip(-1, oldPos, gameBoard);
                
                setPieceToEmpty(checker, oldPos, gameBoard);
                setPieceToFilled(finalPos, gameBoard);
            }else if(checkIfPipIsOpen(finalPos, gameBoard) == 1){
                blotPiece(finalPos, oldPos, gameBoard);
            }else{
                printf("This pip is not open\n");
            }
        }else{
            printf("Cannot find piece\n");
        }
    }


}

void moveTwoPieces(board *gameBoard, int dice[2]){
    /*
    This function moves two pieces
    @param board *gameBoard - pointer to board struct
    @param int dice[2] - array of dice
    */

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
    /*
    This function moves one piece four times
    @param board *gameBoard - pointer to board struct
    @param int dice[2] - array of dice
    */

    int piecePosition; // variable to store the position of the piece to move
    printf("What is the position of the piece that you want to move? ");
    scanf("%d", &piecePosition);
    // if it is player 1's turn
    if(gameBoard->player1turn == true){
        // loop through the possible number of positions to move (4, 8, 12, or 16)
        for(int i = 4; i >= 1; i--){
            // check if the pip that the piece would be moved to is open (does not have more than 1 checker of the same color)
            if (checkIfPipIsOpen(dice[0] * i, gameBoard) == 0){
                printf("You are able to move %d positions\n", dice[0] * i);
                // move the piece the maximum number of positions possible
                movePiece(dice[0] * 4, piecePosition, gameBoard);
                // exit the loop
                i = 0;
            }
        }
    }
    // if it is player 2's turn
    else{
        // loop through the possible number of positions to move (4, 8, 12, or 16)
        for(int i = 4; i >= 1; i--){
            // check if the pip that the piece would be moved to is open (does not have more than 1 checker of the same color)
            if (checkIfPipIsOpen(dice[0] * i, gameBoard) == 0){
                printf("You are able to move %d positions\n", dice[0] * i);
                // move the piece the maximum number of positions possible
                movePiece(dice[0] * 4, piecePosition, gameBoard);
                // exit the loop
                i = 0;

            }
        }

    }
   
}   
int barPromptIfTrue(board *gameBoard){
    /*
    This function prompts the user if they can move a piece from the bar
    @param board *gameBoard - pointer to board struct
    @return int - returns i if the user can move a piece from the bar, -1 if not
    */

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
    /*
    This function shifts the bar
    @param int indexToRemove - index to remove
    @param board *gameBoard - pointer to board struct
    */

    for(int i = indexToRemove; i < gameBoard->barCount; i++){
        gameBoard->playerBar[i] = gameBoard->playerBar[i + 1];
    }
    gameBoard->barCount--;
}

void gameChoice(board *gameBoard, int dice[2]){
    /*
    This function prompts the user for a choice
    @param board *gameBoard - pointer to board struct
    @param int dice[2] - array of dice
    */

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
    /*
    This function prints the bar
    @param board *gameBoard - pointer to board struct
    */

    printf("BAR: \n");
    for(int i = 0; i < gameBoard->barCount; i++){
        printf("Player %d\n", gameBoard->playerBar[i].isPlayerPiece ? 1 : 2);
    }

}
/*
    This function counts the number of pieces each player has
    @param board *gameBoard - pointer to board struct
    @param int playerPieces[2] - array of player pieces
*/
void countPlayerPieces(board * gameBoard, int playerPiecs[]){
    // This function counts the number of pieces each player has

    int amt1 = 0; // variable to store the number of pieces belonging to player 1
    int amt2 = 0; // variable to store the number of pieces belonging to player 2

    // loop through each quadrant on the board
    for(int i = 0; i < 4; i++){
        // loop through each pip in the quadrant
        for(int j = 0; j < 6; j++){
            // loop through each checker in the pip
            for(int k = 0; k < gameBoard->quadrants[i].pips[j].numCheckers; k++){
                // if the checker belongs to player 1 and has not been beared off, increment the count of player 1's pieces
                if (gameBoard->quadrants[i].pips[j].checkersInPip[k].isPlayerPiece == true && gameBoard->quadrants[i].pips[j].checkersInPip[k].bearedOff == false){
                    amt1++;
                }
                // if the checker belongs to player 2 and has not been beared off, increment the count of player 2's pieces
                else if (gameBoard->quadrants[i].pips[j].checkersInPip[k].isPlayerPiece == false && gameBoard->quadrants[i].pips[j].checkersInPip[k].bearedOff == false){
                    amt2++;
                }
            }
        }
    }
    // store the number of pieces belonging to each player in the playerPiecs array
    playerPiecs[0] = amt1;
    playerPiecs[1] = amt2;
}


void printAmtPlayerPieces(board *gameBoard, int playerPieces[]){
    /*
    This function prints the amount of pieces each player has
    @param board *gameBoard - pointer to board struct
    @param int playerPieces[2] - array of player pieces
    */

    countPlayerPieces(gameBoard, playerPieces);
    int amtPlayer1 = playerPieces[0];
    int amtPlayer2 = playerPieces[1];
    
    printf("Player 1 has %d pieces\n", amtPlayer1);
    printf("Player 2 has %d pieces\n", amtPlayer2);
    int amtInHomeBoard1 = 0;
    int amtInHomeBoard2 = 0;
    for(int j = 0; j < 6; j++){
            for(int k = 0; k < gameBoard->quadrants[0].pips[j].numCheckers; k++){
                if (gameBoard->quadrants[0].pips[j].checkersInPip[k].isPlayerPiece == true && gameBoard->quadrants[0].pips[j].checkersInPip[k].bearedOff == false){
                    amtInHomeBoard1++;
                }
            }
    }
    for(int j = 0; j < 6; j++){
            for(int k = 0; k < gameBoard->quadrants[3].pips[j].numCheckers; k++){
                if (gameBoard->quadrants[3].pips[j].checkersInPip[k].isPlayerPiece == false && gameBoard->quadrants[3].pips[j].checkersInPip[k].bearedOff == false){
                    amtInHomeBoard2++;
                }
            }
    }
    printf("Player 1 has %d pieces in home board\n", amtInHomeBoard1);
    printf("Player 2 has %d pieces in home board\n", amtInHomeBoard2);
}

bool checkIfPlayerIsInBearingOffStage(board *gameBoard){
    /*
    This function checks if the player is in the bearing off stage
    @param board *gameBoard - pointer to board struct
    @return bool - true if player is in bearing off stage, false if not
    */

    int playerPieces[2];
    countPlayerPieces(gameBoard, playerPieces);
    int amtInHomeBoard = 0;
    if (gameBoard->player1turn == true && playerPieces[0] > 0){
        for(int j = 0; j < 6; j++){
            for(int k = 0; k < gameBoard->quadrants[0].pips[j].numCheckers; k++){
                if (gameBoard->quadrants[0].pips[j].checkersInPip[k].isPlayerPiece == true && gameBoard->quadrants[0].pips[j].checkersInPip[k].bearedOff == false){
                    amtInHomeBoard++;
                }
            }
        }
        if (amtInHomeBoard == playerPieces[0]){
            printf("You are in the bearing off stage!\n");
            printf("Press y to roll your dice to start bearing off your dice\n");
            char temp;
            scanf(" %c", &temp);
            int result = singularDiceRoll() - 1;
            printf("You rolled a %d\n", result);
            int uBound = 5;
            int lBound = 0;
            int indexOfPieceToBearOff = checkIfPlayerHasPieceInPip(-1, result, gameBoard);
            if (indexOfPieceToBearOff != -1){
                setPieceToBearedOff(indexOfPieceToBearOff, result, gameBoard);
                printf("You have successfully beared off a piece\n");
                return true;
            }else{
                printf("No piece found at %d to bear off\n", result);
                bool hitUpper = false;
                bool hitLower = false;
                while(checkIfPlayerHasPieceInPip(-1, result, gameBoard) == -1 && (hitUpper == false || hitLower == false)){
                    if (result == uBound){
                        
                        hitUpper = true;
                    }else if (result == lBound){
                        
                        hitLower = true;
                    }
                    if (hitUpper == false){
                        
                        result++;
                    }else{
                        
                        result--;
                    }
                    
                    
                    if (checkIfPlayerHasPieceInPip(-1, result, gameBoard) != -1){
                        printf("Found a piece to bear off at %d\n", result);
                        indexOfPieceToBearOff = checkIfPlayerHasPieceInPip(-1, result, gameBoard);
                        setPieceToBearedOff(indexOfPieceToBearOff, result, gameBoard);
                        
                        printf("You have successfully beared off a piece\n");
                        return true;

                    }
                }
                
            }

        }else{
            return false;
        }
    }else if(gameBoard->player1turn == false && playerPieces[1] > 0){
        for(int j = 0; j < 6; j++){
            for(int k = 0; k < gameBoard->quadrants[3].pips[j].numCheckers; k++){
                if (gameBoard->quadrants[3].pips[j].checkersInPip[k].isPlayerPiece == false && gameBoard->quadrants[3].pips[j].checkersInPip[k].bearedOff == false){
                    amtInHomeBoard++;
                }
            }
        }
        if (amtInHomeBoard == playerPieces[1]){
            printf("You are in the bearing off stage!\n");
            printf("Press y to roll your dice to start bearing off your dice\n");
            char temp;
            scanf(" %c", &temp);
            int result = singularDiceRoll() + 17;
            printf("You rolled a %d\n", result);
            int uBound = 23;
            int lBound = 18;
            int indexOfPieceToBearOff = checkIfPlayerHasPieceInPip(-1, result, gameBoard);
            if (indexOfPieceToBearOff != -1){
                setPieceToBearedOff(indexOfPieceToBearOff, result, gameBoard);
                printf("You have successfully beared off a piece\n");
                return true;
            }else{
                printf("No piece found at %d to bear off\n", result);
                bool hitUpper = false;
                bool hitLower = false;
                while(checkIfPlayerHasPieceInPip(-1, result, gameBoard) == -1 && (hitUpper == false || hitLower == false)){
                    if (result == uBound){
                        hitUpper = true;
                    }else if (result == lBound){
                        hitLower = true;
                    }
                    if (hitUpper == false){
                        printf("Incrementing result\n");
                        result++;
                    }else{
                        printf("Decrementing result\n");
                        result--;
                    }
                    printf("Checking %d....\n", result);
                    if (checkIfPlayerHasPieceInPip(-1, result, gameBoard) != -1){
                        printf("Found a piece to bear off at %d\n", result);
                        indexOfPieceToBearOff = checkIfPlayerHasPieceInPip(-1, result, gameBoard);
                        setPieceToBearedOff(indexOfPieceToBearOff, result, gameBoard);
                        
                        printf("You have successfully beared off a piece\n");
                        return true;
                    }
                }
            }
        }else{
            return false;
        }
    }
    return false;
}

void initiateWinInstance(board *gameBoard, int playerPieces[]){
    /*
    This function initiates a win instance
    @param board *gameBoard - pointer to board struct
    @param int playerPieces[] - array of player pieces
    */

    //first case: if a person has borne off all fifteen of his checkers and the opponent 
    // has borne off at least one checker ->  that person wins the current stake
    printf("Player Pieces: %d, %d\n", playerPieces[0], playerPieces[1]);
    printf("Stake: %d\n", gameBoard->stake);
    if (playerPieces[0] == 0 && playerPieces[1] > 0 && playerPieces[1] < 15){
        printf("Player 1 has won the game!\n");
        printf("Player 1 has won %d\n", gameBoard->stake);
    }else if(playerPieces[1] == 0 && playerPieces[0] > 0 && playerPieces[0] < 15){
        printf("Went here\n");
        printf("Player 2 has won the game!\n");
        printf("Player 2 has won %d\n", gameBoard->stake);
    }

    //second case: If the opponent has not borne off any checkers, then the
    //opponent loses a gammon and loses double the current stakes.
    else if(playerPieces[0] == 0 && playerPieces[1] == 15){
        printf("Player 1 has won the game!\n");
        printf("Player 1 has won %d\n", gameBoard->stake * 2);
    }else if(playerPieces[1] == 0 && playerPieces[0] == 15){
        printf("Player 2 has won the game!\n");
        printf("Player 2 has won %d\n", gameBoard->stake * 2);
    }
    //third case:If the opponent has not borne off any checkers and still has one or
    //more checkers on the bar, the opponent loses a backgammon and loses triple the current stakes.
    else if(playerPieces[0] == 0 && playerPieces[1] == 15 && gameBoard->barCount > 0){
        printf("Player 1 has won the game!\n");
        printf("Player 1 has won %d\n", gameBoard->stake * 3);
    }else if(playerPieces[1] == 0 && playerPieces[0] == 15 && gameBoard->barCount > 0){
        printf("Player 2 has won the game!\n");
        printf("Player 2 has won %d\n", gameBoard->stake * 3);
    }
}

/*
    This function gets the dice in debug mode
    @param int dice[] - array of dice
*/
bool getDiceInDebugMode(int dice[2]){
    
    printf("Dice[0]: ");
    scanf("%d", &dice[0]);
    printf("Dice[1]: ");
    scanf("%d", &dice[1]);
    if (dice[0] < 1 || dice[0] > 6 || dice[1] < 1 || dice[1] > 6){
        printf("Invalid dice values\n");
        return false;
    }
    return true;

}

void driver(board* gameBoard){
    /*
    This function is the driver function for the game
    @param board *gameBoard - pointer to board struct
    */
    bool debugMode = false;
    printf("Debug mode? [Y]es or [N]o? \n");
    char temp;
    scanf(" %c", &temp);
    if (temp == 'Y' || temp == 'y'){
        debugMode = true;   
    }
    int playerPieces[2] = {0,0};
    int dice[2];
    bool continuePlaying = true;
    gameBoard->player1turn = true;
    initializeBoard(gameBoard);
    
    do{
        countPlayerPieces(gameBoard, playerPieces);
        if(playerPieces[0] > 0 && playerPieces[1] > 0){
            displayGame(gameBoard);
            printBar(gameBoard);
            printAmtPlayerPieces(gameBoard, playerPieces);
            printf("Player %s's turn\n", gameBoard->player1turn ? "1" : "2");
            printf("Current stake: %d\n", gameBoard->stake);
            printf("Current Owner of stake: %s\n", gameBoard->player1OwnerStake ? "Player 1" : "Player 2");
            if (debugMode == true){
                bool result;
                do{
                    result = getDiceInDebugMode(dice);
                }while(result == false);
             
            }else{
                doubleDiceRoll(dice);
            }
            
            if(playerPieces[0] > 0 && playerPieces[1] > 0){
                if(!checkIfPlayerIsInBearingOffStage(gameBoard)){
                    gameChoice(gameBoard, dice);
                    

                }
                changeTurn(gameBoard);
            }
            
        }else{
            initiateWinInstance(gameBoard, playerPieces);
            continuePlaying = false;
        }

        
        
        
        


    }while(continuePlaying == true );

}


int main(){
    board gameBoard;
    driver(&gameBoard);
    return 0;


}
