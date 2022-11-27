#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
typedef struct checker{
    bool isPlayerPiece;
    bool insideBar;
    bool bearedOff;
    int position;
}checker;

typedef struct pip{
    bool isEmpty;
    int checkerCount;
    checker checkers[30];

} pip;

typedef struct quadrant{
    int quadrantNumber;
    pip pips[6];
}quadrant;


typedef struct bar{
    
    checker checkers[30];
} bar;
typedef struct board{
    int barCount;
    quadrant quadrants[4];
    bar playerBar;
} board;

typedef struct player{
    bool isPlayerTurn;
    int checkerCount;
    checker playerChecker[15];
} player;


typedef struct game{
    player player1;
    player player2;
    board gameBoard;
} game;


void initPlayerPieces(game *game){
    for(int i = 0; i < 15; i++){
        game->player1.playerChecker[i].isPlayerPiece = true;
        game->player1.playerChecker[i].insideBar = false;
        game->player1.playerChecker[i].bearedOff = false;
        game->player1.playerChecker[i].position = 0;
        game->player2.playerChecker[i].isPlayerPiece = false;
        game->player2.playerChecker[i].insideBar = false;
        game->player2.playerChecker[i].bearedOff = false;
        game->player2.playerChecker[i].position = 0;
    }

}

void initializeGame(game *game){
    srand(time(NULL));
    game->player1.isPlayerTurn = true;
    game->player2.isPlayerTurn = false;
    for(int i = 0; i < 4; i++){
        game->gameBoard.quadrants[i].quadrantNumber = i + 1;
        for(int j = 0; j < 6; j++){
            game->gameBoard.quadrants[i].pips[j].isEmpty = true;
            game->gameBoard.quadrants[i].pips[j].checkerCount = 0;
            
        }
    }
    game->gameBoard.barCount = 0;
    
    game->player1.checkerCount = 15;
    game->player2.checkerCount = 15;
    int pPositions[4] = {23,12,7,5};
    int oPositions[4] = {0, 11, 16, 18};
    int initQty[4] = {2, 5, 3, 5};
    int count = 0;

    initPlayerPieces(game);
    

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < initQty[i]; j++){
            
            
            int coord = pPositions[i];
            int q = (coord / 6);
            
            game->gameBoard.quadrants[q].pips[coord % 6].checkerCount++;
            game->gameBoard.quadrants[q].pips[coord % 6].isEmpty = false;

            game->player1.playerChecker[count].position = coord;
            game->gameBoard.quadrants[q].pips[coord % 6].checkers[j] = game->player1.playerChecker[count];
            
            
            
            count++;

        }
    }
    count = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < initQty[i]; j++){
            
            int coord = oPositions[i];
            int q = (coord / 6);
            game->gameBoard.quadrants[q].pips[coord % 6].checkerCount++;
            game->gameBoard.quadrants[q].pips[coord % 6].isEmpty = false;


            game->player2.playerChecker[count].position = coord;
            game->gameBoard.quadrants[q].pips[coord % 6].checkers[j] = game->player2.playerChecker[count];
            
            count++;

        }
    }
    
    
}
int getMaxInQuadrant(quadrant q){
    int max = 0;
    for (int i = 0; i < 6; i++){
        
        if (max < q.pips[i].checkerCount){
            max = q.pips[i].checkerCount;
        }
    }
    return max;

}
void displayGame(game *game){
    for (int i = 12; i < 24; i++){
        printf(" %d ", i);
    }
    //max gets the number of checkers in the quadrant with the most checkers
    int max = getMaxInQuadrant(game->gameBoard.quadrants[3]) < getMaxInQuadrant(game->gameBoard.quadrants[2]) ? getMaxInQuadrant(game->gameBoard.quadrants[2]) : getMaxInQuadrant(game->gameBoard.quadrants[3]);
    printf("\n");
    for(int i = 0; i < max; i++){
        for(int j = 12; j < 24; j++){
            int q = j/6;
            int p = j % 6;
            if(game->gameBoard.quadrants[q].pips[p].isEmpty){
                printf("    ");
            }
            else{
                if(game->gameBoard.quadrants[q].pips[p].checkerCount > i){
                    if(game->gameBoard.quadrants[q].pips[p].checkers[i].isPlayerPiece && game->gameBoard.quadrants[q].pips[p].checkers[i].insideBar == false){
                        printf(" ++ ");
                    }
                    else if (game->gameBoard.quadrants[q].pips[p].checkers[i].isPlayerPiece == false && game->gameBoard.quadrants[q].pips[p].checkers[i].insideBar == false){
                    
                        printf(" -- ");
                    }else{
                        printf("    ");
                    }
                }
                else{
                    printf("    ");
                }
            }
        }
        printf("\n");
    }
    printf("------------------------------------------------\n");
    for (int i = 11; i >= 0; i--){
        if (i >= 10){
            printf(" %d ", i);
        }
        else{
            printf(" 0%d ", i);
        }        
    }
    max = getMaxInQuadrant(game->gameBoard.quadrants[1]) < getMaxInQuadrant(game->gameBoard.quadrants[0]) ? getMaxInQuadrant(game->gameBoard.quadrants[0]) : getMaxInQuadrant(game->gameBoard.quadrants[1]);
    printf("\n");
    for(int i = 0; i < max; i++){
        for(int j = 11; j >= 0; j--){
            int q = j/6;
            int p = j % 6;
            if(game->gameBoard.quadrants[q].pips[p].isEmpty){
                printf("    ");
            }
            else{
                if(game->gameBoard.quadrants[q].pips[p].checkerCount > i){
                    if(game->gameBoard.quadrants[q].pips[p].checkers[i].isPlayerPiece && game->gameBoard.quadrants[q].pips[p].checkers[i].insideBar == false){
                        printf(" ++ ");
                    }
                    else if (game->gameBoard.quadrants[q].pips[p].checkers[i].isPlayerPiece == false && game->gameBoard.quadrants[q].pips[p].checkers[i].insideBar == false){
                    
                        printf(" -- ");
                    }else if(game->gameBoard.quadrants[q].pips[p].checkers[i].insideBar == true){
                        printf("    ");
                    }
                }
                else{
                    printf("    ");
                }
            }
        }
        printf("\n");
    }
    printf("------------------------------------------------\n");
    printf("%10s%d\n", "\nBAR:\t|Bar Count: ", game->gameBoard.barCount);
    for(int i = 0; i < game->gameBoard.barCount; i++){
        if(game->gameBoard.playerBar.checkers[i].isPlayerPiece){
            printf(" ++ ");
        }
        else{
            printf(" -- ");
        }
    }

}

void rollDice(int *dice){
    dice[0] = rand() % 6 + 1;
    dice[1] = rand() % 6 + 1;
}


int checkIfPipIsOpen(int amountToMove, int checkerIndex, int dice[], game *game){
    if (game->player1.isPlayerTurn == true){
        int initialPos = game->player1.playerChecker[checkerIndex].position;
        int finalPos = initialPos - amountToMove;
        if(finalPos < 0){
            finalPos = -1;
        }else{
            int count = 0;
            for(int i = 0; i < 15;i++){
                if(game->player2.playerChecker[i].position == finalPos){
                    count++;
                }
            }
            if (count > 1){
                return -1;
            }else{
                return finalPos;
            }
        }
    }else{
        int initialPos = game->player2.playerChecker[checkerIndex].position;
        int finalPos = initialPos + amountToMove;
        if (finalPos > 23){
            finalPos = -1;
        }else{
            int count = 0;
            for(int i = 0; i < 15;i++){
                if(game->player1.playerChecker[i].position == finalPos){
                    count++;
                }
            }
            if (count > 1){
                return -1;
            }else{
                return finalPos;
            }
        }
        
    }
    return -1;

}

int countOppPiecesAtPip(int position, game *game){
    int count = 0;
    if (game->player1.isPlayerTurn == true){
        for(int i = 0; i <15; i++){
            if (game->player2.playerChecker[i].position == position){
                count++;
            }
        }
    }else{
        for(int i = 0; i <15; i++){
            if (game->player1.playerChecker[i].position == position){
                count++;
            }
        }
    }
    return count;
}

int lookForBoardPiece(int protocol, int position, game *game){
    if (protocol == 1){
        if (game->player1.isPlayerTurn == true){
        int q = position / 6;
        int p = position % 6;
        for(int i = 0; i < game->gameBoard.quadrants[q].pips[p].checkerCount; i++){
            if (game->gameBoard.quadrants[q].pips[p].checkers[i].isPlayerPiece == true){
                return i;
            }
        }
        }else{
            int q = position / 6;
            int p = position % 6;
            for(int i = 0; i < game->gameBoard.quadrants[q].pips[p].checkerCount; i++){
                if (game->gameBoard.quadrants[q].pips[p].checkers[i].isPlayerPiece == false){
                    return i;
                }
            }
        }
    }else{
        if (game->player1.isPlayerTurn == false){
            int q = position / 6;
            int p = position % 6;
            for(int i = 0; i < game->gameBoard.quadrants[q].pips[p].checkerCount; i++){
                if (game->gameBoard.quadrants[q].pips[p].checkers[i].isPlayerPiece == true){
                    return i;
                }
            }
        }else{
            int q = position / 6;
            int p = position % 6;
            for(int i = 0; i < game->gameBoard.quadrants[q].pips[p].checkerCount; i++){
                if (game->gameBoard.quadrants[q].pips[p].checkers[i].isPlayerPiece == false){
                    return i;
                }
            }
        }
    }
    return -1;

}
void movePieceToNewPos(int pieceIndex, int finalPos, game *game){
    if(game->player1.isPlayerTurn){
        int q = finalPos/6;
        int p = finalPos % 6;
        int oldPos = game->player1.playerChecker[pieceIndex].position;
        //steps to do:
        //1. remove piece from old position
        game->player1.playerChecker[pieceIndex].position = finalPos;
        //2. add piece to new position
        game->gameBoard.quadrants[q].pips[p].checkers[game->gameBoard.quadrants[q].pips[p].checkerCount] = game->player1.playerChecker[pieceIndex];
        //3.decrement old position checker count
        game->gameBoard.quadrants[oldPos/6].pips[oldPos%6].checkerCount--;
        //4. increment new position checker count
        game->gameBoard.quadrants[q].pips[p].checkerCount++;
        game->gameBoard.quadrants[q].pips[p].isEmpty = false;
    }else{
        int q = finalPos/6;
        int p = finalPos % 6;
        int oldPos = game->player2.playerChecker[pieceIndex].position;
        //steps to do:
        //1. remove piece from old position
        game->player2.playerChecker[pieceIndex].position = finalPos;
        //2. add piece to new position
        game->gameBoard.quadrants[q].pips[p].checkers[game->gameBoard.quadrants[q].pips[p].checkerCount] = game->player2.playerChecker[pieceIndex];
        //3.decrement old position checker count
        game->gameBoard.quadrants[oldPos/6].pips[oldPos%6].checkerCount--;
        //4. increment new position checker count
        game->gameBoard.quadrants[q].pips[p].checkerCount++;
        game->gameBoard.quadrants[q].pips[p].isEmpty = false;
    }
    

}

void changeTurn(game *game){
    if(game->player1.isPlayerTurn){
        game->player1.isPlayerTurn = false;
        game->player2.isPlayerTurn = true;
    }else{
        game->player1.isPlayerTurn = true;
        game->player2.isPlayerTurn = false;
    }

}
void blotPiece(int finalPos, int pieceIndex, game *game, int dice[]){
    if (game->player1.isPlayerTurn == true){
        if (countOppPiecesAtPip(finalPos, game) == 1){
            int c = game->gameBoard.quadrants[finalPos/6].pips[finalPos%6].checkerCount;
            int pieceToBlot = lookForBoardPiece(2,finalPos, game);
            for (int i = 0;i < c ;i++){
                if (game->gameBoard.quadrants[finalPos/6].pips[finalPos%6].checkers[i].isPlayerPiece == false){
                    game->gameBoard.quadrants[finalPos/6].pips[finalPos%6].checkers[i].insideBar = true;
                    game->gameBoard.quadrants[finalPos/6].pips[finalPos%6].checkerCount--;
                    i = c;
                }
            }
            
            game->player2.playerChecker[pieceToBlot].insideBar = true;
            game->player2.playerChecker[pieceToBlot].position = -1;
            game->gameBoard.playerBar.checkers[game->gameBoard.barCount] = game->player2.playerChecker[pieceToBlot];
            
            movePieceToNewPos(pieceIndex, finalPos, game);
            changeTurn(game);
            game->gameBoard.barCount++;
        }
    }else{
        if (countOppPiecesAtPip(finalPos, game) == 1){
            int c = game->gameBoard.quadrants[finalPos/6].pips[finalPos%6].checkerCount;
            int pieceToBlot = lookForBoardPiece(2,finalPos, game);
            for (int i = 0;i < c ;i++){
                if (game->gameBoard.quadrants[finalPos/6].pips[finalPos%6].checkers[i].isPlayerPiece == true){
                    game->gameBoard.quadrants[finalPos/6].pips[finalPos%6].checkers[i].insideBar = true;
                    game->gameBoard.quadrants[finalPos/6].pips[finalPos%6].checkerCount--;
                    i = c;
                }
            }


            
            game->player1.playerChecker[pieceToBlot].insideBar = true;
            game->player1.playerChecker[pieceToBlot].position = -1;
            game->gameBoard.playerBar.checkers[game->gameBoard.barCount] = game->player1.playerChecker[pieceToBlot];
            
            movePieceToNewPos(pieceIndex, finalPos, game);
            changeTurn(game);
            game->gameBoard.barCount++;
        }
    }
}
void movePiece(int protocol, int pieceIndex,game *game, int dice[]){
    if (game->player1.isPlayerTurn == true){
        if (protocol == 1){
            int finalPos = checkIfPipIsOpen(dice[0]+dice[1], pieceIndex, dice, game);
            if (finalPos == -1){
                printf("You cannot move this piece\n");
            }else{
                if (countOppPiecesAtPip(finalPos, game) == 0){
                    movePieceToNewPos(pieceIndex, finalPos, game);
                    changeTurn(game);
                }else{
                    blotPiece(finalPos, pieceIndex, game, dice);
                }
            }
        }
    }else{
        if (protocol == 1){
            int finalPos = checkIfPipIsOpen(dice[0]+dice[1], pieceIndex, dice, game);
            if (finalPos == -1){
                printf("You cannot move this piece\n");
            }else{
                if (countOppPiecesAtPip(finalPos, game) == 0){
                    movePieceToNewPos(pieceIndex, finalPos, game);
                    changeTurn(game);
                }else{
                    blotPiece(finalPos, pieceIndex, game, dice);
                }
            }
        }
    }

}





void moveTwoPieces(int pieceIndex1, int pieceIndex2, game *game, int dice[]){
    if (game->player1.isPlayerTurn){
        int finalPos1 = checkIfPipIsOpen(dice[0], pieceIndex1, dice, game);
        int finalPos2 = checkIfPipIsOpen(dice[1], pieceIndex2, dice, game);
        if (finalPos1 == -1 || finalPos2 == -1){
            printf("You cannot move these pieces\n");
            moveTwoPieces(pieceIndex1, pieceIndex2, game, dice);
        }else{
            if (countOppPiecesAtPip(finalPos1, game) == 0 && countOppPiecesAtPip(finalPos2,game) == 0){
                movePieceToNewPos(pieceIndex1, finalPos1, game);
                movePieceToNewPos(pieceIndex2, finalPos2, game);
                changeTurn(game);

            }
        }

    }

}

void moveOnePieceFourPlaces(int pieceIndex, game *game, int dice[]){
        int finalPos; 
        for(int i = 4; i > 0; i--){
            finalPos = checkIfPipIsOpen(dice[0] * i, pieceIndex, dice, game);
            if (finalPos == -1){
                continue;
            }else{
                int choice;
                printf("You can move this piece %d places\n", dice[0] * i);
                printf("Do you want to choose this move? (1 for yes, 0 for no)\n");
                scanf("%d", &choice);
                if (choice == 0){
                    i = 0;
                    finalPos = -1;
                }else{ 
                    finalPos = checkIfPipIsOpen(dice[0] * i, pieceIndex, dice, game);
                    i = 0;
                }
            }
        }
        if (finalPos == -1){
            printf("You cannot move this piece\n");

        }else{
            if (countOppPiecesAtPip(finalPos, game) == 0){
                movePieceToNewPos(pieceIndex, finalPos, game);
                changeTurn(game);
            }else{
                blotPiece(finalPos, pieceIndex, game, dice);
            }
        }
    

    
}
    

int lookForPieceInPlayerCheckers(int indexIgnore, int posToLookFor, game *game){
    if(game->player1.isPlayerTurn == true){
        for(int i = 0; i < 15; i++){
            if(i != indexIgnore){
                if(game->player1.playerChecker[i].position == posToLookFor){
                    return i;
                }
            }
        }
    }else if(game->player2.isPlayerTurn == true){
        for(int i = 0; i < 15; i++){
            if(i != indexIgnore){
                if(game->player2.playerChecker[i].position == posToLookFor){
                    return i;
                }
            }
        }
    }
    return -1;
}

void askForPiece(int choice, game *game, int dice[]){
    if (choice == 1){
        int piecePosition;
        printf("Enter the position of the piece you want to move: ");
        scanf("%d", &piecePosition);
        int index = lookForPieceInPlayerCheckers(-1, piecePosition, game);
        if(index != -1){
            movePiece(choice,index, game, dice);
        }
        else{
            printf("You do not have a piece at that position\n");
            askForPiece(choice, game, dice);
        }

    }else if(choice == 2){
        int piecePosition1;
        int piecePosition2;
        printf("Enter the position of the first piece you want to move %d positions: ", dice[0]);
        scanf("%d", &piecePosition1);
        printf("Enter the position of the second piece you want to move %d positions: ", dice[1]);
        scanf("%d", &piecePosition2);
        int index1 = lookForPieceInPlayerCheckers(-1, piecePosition1, game);
        int index2 = lookForPieceInPlayerCheckers(index1, piecePosition2, game);
        if(index1 != -1 && index2 != -1){
            moveTwoPieces(index1, index2, game, dice);
        }
        else{
            printf("You do not have a piece at that position\n");
            askForPiece(choice, game, dice);
        }
        
    }else if(choice == 3 && dice[0] == dice[1]){
        int piecePosition;
        printf("Enter the position of the piece you want to move %d positions: ", dice[0] * 4);
        scanf("%d", &piecePosition);
        int index = lookForPieceInPlayerCheckers(-1, piecePosition, game);
        moveOnePieceFourPlaces(index, game, dice);
    }
}




void giveChoices(game *game, int dice[]){
    int choice;
    printf("It is Player %d's turn\n", game->player1.isPlayerTurn == true ? 1 : 2);
    printf("These are your choices: \n");
    printf("[1] Move one piece %d spaces\n", dice[0] + dice[1]);
    printf("[2] Move two pieces seperately with one piece %d spaces\nand the other %d spaces\n", dice[0], dice[1]);
    if (dice[0] == dice[1]){
        printf("[3] Move one piece up to %d spaces in increments of %d\n", dice[0] * 4, dice[0]);
    }
    printf("Enter your choice: ");
    scanf("%d", &choice);
    askForPiece(choice, game, dice);
}
bool checkIfPosIsOpen(int pos, game *game){
    if (game->player1.isPlayerTurn){
        int count = 0;
        int q = pos / 6;
        int p = pos % 6;
        for(int i = 0;i < game->gameBoard.quadrants[q].pips[p].checkerCount; i++){
            if(game->gameBoard.quadrants[q].pips[p].checkers[i].isPlayerPiece == false){
                count++;
            }
        }
        if (count <= 1){
            return true;
        }else{
            return false;
        }
    }else{
        int count = 0;
        int q = pos / 6;
        int p = pos % 6;
        for(int i = 0;i < game->gameBoard.quadrants[q].pips[p].checkerCount; i++){
            if(game->gameBoard.quadrants[q].pips[p].checkers[i].isPlayerPiece == true){
                count++;
            }
        }
        if (count <= 1){
            return true;
        }else{
            return false;
        }


    }

}
bool barCheck(game *game){
    char t;
    if (game->gameBoard.barCount > 0){
        if (game->player1.isPlayerTurn == true){
            for(int i = 0; i < game->gameBoard.barCount; i++){
                if(game->gameBoard.playerBar.checkers[i].isPlayerPiece == true){
                    int dice[2];
                    
                    printf("You have a checker on the bar, you must move it before you can move any other checkers\n");
                    printf("Roll dice? press anything to continue: ");
                    scanf(" %c", &t);
                    rollDice(dice);
                    if (checkIfPosIsOpen(17+dice[0], game) == true){
                        int pieceIndex = lookForPieceInPlayerCheckers(-1, -1, game);
                        movePieceToNewPos(pieceIndex, 17+dice[0], game);
                        changeTurn(game);
                        
                    }else{
                        printf("Your dice did not land on a valid position\n");
                        changeTurn(game);
                    }
                    return true;

                }
            }
        }else{
            if (game->player1.isPlayerTurn == false){
                for(int i = 0; i < game->gameBoard.barCount; i++){
                    if(game->gameBoard.playerBar.checkers[i].isPlayerPiece == false){
                        int dice[2];
                        printf("You have a checker on the bar, you must move it before you can move any other checkers\n");
                        printf("Roll dice? press anything to continue: ");
                        scanf(" %c",&t);
                        rollDice(dice);
                        if (checkIfPosIsOpen(dice[0], game) == true){
                            int pieceIndex = lookForPieceInPlayerCheckers(-1, -1, game);
                            movePieceToNewPos(pieceIndex, dice[0], game);
                            changeTurn(game);
                            
                        }else{
                            printf("Your dice did not land on a valid position\n");
                            changeTurn(game);
                        }
                        return true;
                    }
                }
            }

        }
    }else{
        return false;
    }
    return false;


}
void startGame(game *game){
    int dice[2];
    bool continuePlaying = true;
    bool player1turn = game->player1.isPlayerTurn;
    initializeGame(game);
    do{
        
        
        // rollDice(dice);
        if (!barCheck(game)){

            displayGame(game);
            printf("\n\nDice [0]: "); 
            scanf("%d", &dice[0]);
            printf("Dice [1]: "); scanf("%d", &dice[1]);
            printf("\nPlayer %d rolled a %d and a %d\n",game->player1.isPlayerTurn ? 1 : 2, dice[0], dice[1]);
            giveChoices(game, dice);

        }
        

    }while(continuePlaying == true);

    
}



