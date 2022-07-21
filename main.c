/*
* ----- Credits -----
* https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
* https://www.programiz.com/dsa/ford-fulkerson-algorithm
*
* Author : Ece Yucer 
* Link: https://github.com/yucerece
*
*/


#include "split.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    int loop = 1, i = 0, indexcredit = 0, people = 0, debtorsindex[MAX], ishappened = 0, j;
    int numofpeople = 0, count = 0, description_count = 0;
    char groupname[30], name[10], description[10], line[50];
    float money = 0, totalmoney = 0, maxflow = 0;
    MemberInfo* memberInfos;
    FILE *fpt;
    //Baslangic
    printf("----------Welcome to the SettlEasy---------- \n\nFirst, let's create group. Then, determine the members.");
    printf("\nEnter the name of the group : ");
    scanf("%[^\n]%*c", groupname);

    char buf[0x100];
    snprintf(buf, sizeof(buf), "%s.csv", groupname);
    fpt = fopen(buf, "w+");

    //gruba isim belirle.
    //printf("%s", groupname);
    printf("\nHow many people there will be in this group? ");
    scanf("%d", &numofpeople);

    float csvlist[numofpeople];

    memberInfos= (MemberInfo*) calloc(numofpeople, sizeof(memberInfos));
    printf("\nEnter name of the members one by one : \n");
    for(int i = 0; i < numofpeople; i++){
        scanf("%s", name);
        strcpy(memberInfos[i].name, name);
    }

    fprintf(fpt,"Description, Category, Total Expense");
    for(int k = 0; k < numofpeople; k++){
        fprintf(fpt,", ");
        fprintf(fpt,"%s", memberInfos[k].name);
    }
    fprintf(fpt,"\n");
    printf("\nThe group has been created.\n");

    float **expenseGraph;
    expenseGraph = (float **)malloc(numofpeople * sizeof(float *));
    for (int r = 0; r < numofpeople; r++) {
        expenseGraph[r] = (float *)malloc(numofpeople * sizeof(float));
    }
    for(int j = 0; j < numofpeople; j++){
        for(int k = 0; k < numofpeople; k++) expenseGraph[j][k] = 0;
    }

    float **rGraph;
    rGraph = (float **)malloc(numofpeople * sizeof(float *));
    for(int r = 0; r < numofpeople; r++) rGraph[r] = (float *)malloc(numofpeople * sizeof(float));


    while(loop){ 
        printf("\n----------------------MENU----------------------\n");
        printf("1 : Add an expense.\n");
        printf("2 : Display who pays who.\n");
        printf("3 : Do the magic.\n");
        printf("4 : Display the balance of a certain user.\n");
        printf("5 : Exit the menu.\n");

        scanf("%d", &i);

        switch(i){
            case 1:
                printf("\nWho pays? ");
                scanf("%s", name);
                indexcredit = getIndexofthemem(memberInfos, name, numofpeople);
                printf("\nEnter the description : ");
                scanf("%s", description);

                printf("\nEnter the amount of the expense : ");
                scanf("%f", &money);
                totalmoney = money;
                printf("\nHow many people are you gonna split with? (including you) ");
                scanf("%d", &people);
                printf("\n");
                
                for(int k = 0; k < numofpeople; k++) csvlist[k] = 0;
                money = (money/people);
                csvlist[indexcredit] = money;
                ishappened = 0;

                if(isInteger(totalmoney) == 1) fprintf(fpt, "%s, General, %d", description, (int)totalmoney);
                else fprintf(fpt, "\n%s, General, %.2f", description, totalmoney);
                if((1 < people) && (people < numofpeople)){
                    ishappened = 1;
                    printf("\nEnter the names you pay for (one by one) : ");
                    for(int g = 0; g < people - 1; g++){
                        scanf("%s", name);
                        debtorsindex[g] = getIndexofthemem(memberInfos, name, numofpeople);
                    }
                }
                if(ishappened != 1){
                    for(int k = 0; k < numofpeople; k++){
                        if(k == indexcredit) continue;
                        csvlist[k] = -money;
                    }
                }
                else{
                    for(int g = 0; g < people - 1; g++){
                        csvlist[debtorsindex[g]] = -money;
                    }
                }

                for(int g = 0; g < numofpeople; g++){
                    if(isInteger(csvlist[g]) == 1) fprintf(fpt, ", %d", (int)csvlist[g]);
                    else fprintf(fpt, ", %.2f", csvlist[g]);
                }
                fprintf(fpt, "\n");

                if(ishappened == 1){
                    for(int z = 0; z < people - 1; z++){
                    expenseGraph[debtorsindex[z]][indexcredit] = money;
                    }
                }
                else{
                    for(int y = 0; y < people; y++){
                        if(y == indexcredit) continue;
                        expenseGraph[y][indexcredit] = money;
                    }
                }    
                for(int i = 0; i < numofpeople; i++){
                    for(int k = 0; k < numofpeople; k++) rGraph[i][k] = expenseGraph[i][k];
                }    
                break;

            case 2:
                printf("\n");
                for(int i = 0; i < numofpeople; i++){
                    for(int k = 0; k < numofpeople; k++){
                        if(expenseGraph[i][k] != 0){
                            if((i == 0) && (k == (numofpeople-1))){
                                if(isInteger(expenseGraph[i][k]+maxflow) == 1) printf("%s owes %d TL to %s.\n", memberInfos[i].name, (int)(expenseGraph[i][k]+maxflow), memberInfos[k].name);
                                else printf("%s owes %.2f TL to %s.\n", memberInfos[i].name, expenseGraph[i][k] +maxflow, memberInfos[k].name);
                                continue;
                            } 
                            if(isInteger(expenseGraph[i][k]) == 1) printf("%s owes %d TL to %s.\n", memberInfos[i].name, (int)expenseGraph[i][k], memberInfos[k].name);
                            else printf("%s owes %.2f TL to %s.\n", memberInfos[i].name, expenseGraph[i][k], memberInfos[k].name);
                        }
                    }
                    if((i == 0) && (maxflow != 0)){
                        if(isInteger(maxflow) == 1) printf("%s owes %d TL to %s.\n", memberInfos[0].name, (int)maxflow, memberInfos[5].name);
                        else printf("%s owes %.2f TL to %s.\n", memberInfos[0].name, maxflow, memberInfos[5].name);
                    }
                }
                break;
        
            case 3:
                printf("\nThe spell has been cast. Piertotum Locomotor...\n\n");
                maxflow += fordFulkerson(expenseGraph, rGraph, 0, numofpeople-1);
                if(isInteger(maxflow) == 1) printf("Maxflow is %d.\n", (int)maxflow);
                else printf("\nMaxflow is %.2f.\n", maxflow);
                printf("\nThe final state of the expenses in an array :\n");
                for(int i = 0; i < numofpeople; i++){
	                printf("\n");
	                for(int k = 0; k < numofpeople; k++){
                        if(isInteger(expenseGraph[i][k]) == 1) printf("%-6d ", (int)expenseGraph[i][k]);
	                    else printf("%-6.2f ", expenseGraph[i][k]);
	                }
	            }
                printf("\n");
                break;

            case 4:
                printf("\nEnter a name : ");
                scanf("%s", name);
                printf("\n");
                int index = getIndexofthemem(memberInfos, name, numofpeople);
                float maxflow_ = 0;
                for(int j = 0; j < numofpeople; j++){
                    if((index == 0) && (j == (numofpeople-1))) maxflow_ = maxflow;
                    if(expenseGraph[index][j] != 0){
                        if(isInteger(expenseGraph[index][j]) == 1) printf("%s owes %d TL to %s.\n", memberInfos[index].name, (int)expenseGraph[index][j] + (int)maxflow_, memberInfos[j].name);
                        else printf("%s owes %.2f TL to %s.\n", memberInfos[index].name, expenseGraph[index][j] + maxflow_, memberInfos[j].name);
                    }
                    else if((index == 0) && (expenseGraph[index][j] == 0 && (j == (numofpeople-1)))){
                        if(isInteger(expenseGraph[index][j]) == 1) printf("%s owes %d TL to %s.\n", memberInfos[index].name, (int)maxflow_, memberInfos[j].name);
                        else printf("%s owes %.2f TL to %s.\n", memberInfos[index].name, maxflow_, memberInfos[j].name);
                    }
                    maxflow_ = 0;
                }
                break;

            case 5: 
                loop = 0;
                break;

            default:
                printf("Please Enter a Valid Choice\n");
                break;
        }
    }
    fclose(fpt);
    //deallocate memories
    free(memberInfos);
    memberInfos = NULL;
    for (i = 0; i < numofpeople; i++) {
        free(expenseGraph[i]);
        expenseGraph[i] = NULL;
    }
    free(expenseGraph);
    expenseGraph = NULL;
    for (i = 0; i < numofpeople; i++) {
        free(rGraph[i]);
        rGraph[i] = NULL;
    }
    free(rGraph);
    rGraph = NULL;
    return 0;
}

//lol