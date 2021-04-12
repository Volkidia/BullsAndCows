// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Kismet/KismetSystemLibrary.h"

/**
 * Display the welcome message
 */ 
void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    ClearScreen();
    PrintLine(TEXT("Welcome to Bulls Cows Game !"));
    PrintLine(TEXT("Press Enter to start playing !"));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{

    FString OutPrompt = "";
    switch (Gamestate)
    {
    //Game initialisation
    case 0:
        ClearScreen();
        SetupGame();
        PrompGameStart();
        break;

    //Game logic
    case 1:


        if(Input == Hiddenword)
        {
            PrompGameEnd(true);
            return;
        }

        if(!VerifyInputCarac(Input, OutPrompt))
        {
            PrintLine(TEXT("%s"), *OutPrompt);
            return;
        }

        Lives--;

        if (Lives < 1)
        {
            PrompGameEnd(false);
            return;
        }
        
        PrintLine(TEXT("You didn't guess the correct word."));
        PrintLine(GiveClue(*Input));
        PrintLine(TEXT("You now have : %i lives remaining !"), Lives);

        break;

    //End of Game State
    default:
        if (Input.ToLower() == TEXT("no"))
        {
            UKismetSystemLibrary::QuitGame(this, nullptr,EQuitPreference::Quit, true);
        }
        else
        {
            ClearScreen();
            SetupGame();
            PrompGameStart();
        }
        
        break;
    }
}

/**
 * Initialize all Game variables to their Start values
 */
void UBullCowCartridge::SetupGame()
{   
    // Init game values
    Hiddenword = GenerateGuessWord();
    Lives = Hiddenword.Len();
    Gamestate = 1;
}

/**
 * Promp the Game start text to the player 
 */
void UBullCowCartridge::PrompGameStart()
{
    //Promp game infos
    PrintLine(
        TEXT("Guess the %i letters word\nthen press Enter to continue !\nYou have %i lives to do so !"),
            Hiddenword.Len(), Hiddenword.Len());
}

/**
 * Promp the End game message to the payer depending of the last game result
 * 
 * @param IsWin Is the last game result
 */
void UBullCowCartridge::PrompGameEnd(bool Iswin)
{
    if (Iswin)
        PrintLine(
            TEXT("You Won ! You guessed the word ! The word was : %s"), 
                *Hiddenword);
    else
        PrintLine(
            TEXT("You Lost ! The word was %s"), 
                *Hiddenword); 

    PrintLine(
        TEXT("Press Enter to continue \nor type \"no\" and Enter to quit."));

    Gamestate = 2;      
}

/**
 * Check if the word given has the right caracteristics (correct number of letter AND is an Isogram)
 * 
 * @param Word contain the word to test (usually player input)
 * @param OutLog Output the promp message to display
 * @return if the word given has the correct number of letter AND is an Isogram or not
 */ 
bool UBullCowCartridge::VerifyInputCarac(const FString& Word, FString& OutLog)
{
    if (Word.Len() != Hiddenword.Len())
    {
        OutLog =  FString::Printf(TEXT("Your guess doesn't have the correct \nnumber of Letters (%i) !"),
                        Hiddenword.Len());
        return false;
    }
    else if(!IsIsogram(Word))
    {
        OutLog = FString::Printf(TEXT("Your word is not an Isogram !"));
        return false;
    }
    OutLog = "";
    return true;   
}

/**
 * Check if the the input is an Isogram (no double letters)
 * 
 * @param Input The word to be tested
 * @return Is the Input an Isogram or not
 */ 
bool UBullCowCartridge::IsIsogram(FString Input) const
{
    FString ToLowerInput = Input.ToLower();
    bool IsIsogramConfirmed = true;    
	CHAR c = ToLowerInput[0];
	int32 i = 0;
    while (ToLowerInput.Len() > 1 && IsIsogramConfirmed)
    {
        c = ToLowerInput[0];
        ToLowerInput.RemoveAt(0,1,true);
        IsIsogramConfirmed = !ToLowerInput.FindChar(c,i);
    }
    return IsIsogramConfirmed;
}

/**
 * Select a word at random in THiddenWords (TArray<FString>)
 * 
 * @return The choosen word selected at random
 */
FString UBullCowCartridge::GenerateGuessWord()
{
    return THiddenWords[FMath::RandRange(0,THiddenWords.Max())];
}


/**
 * Give the information to the player about his last try
 * 
 * @param Input The word to be tested
 * @return The Text to be displayed
 */
FString UBullCowCartridge::GiveClue(const FString& Input)
{
    FString ClueLine = TEXT("### CLUE ###\n");
    int32 OutI;
    
    for(int32 i = 0; i <= Input.Len()-1; i++)
    {
        if(Hiddenword.FindChar(Input[i], OutI))
            if(OutI == i)
                ClueLine.Append(TEXT("BULL"));
            else
                ClueLine.Append(TEXT("COW"));
        else
            ClueLine.Append(TEXT("---"));

        if (i<= Input.Len()-2)
            ClueLine.Append(TEXT(" , "));        
    }
    return ClueLine;
}