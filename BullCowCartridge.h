// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "HiddenWordList.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetupGame();
	void PrompGameStart();
	void PrompGameEnd(bool Iswin);
	FString GenerateGuessWord();
	bool VerifyInputCarac(const FString& Word, FString& OutLog);
	bool IsIsogram(FString Input) const;
	FString GiveClue(const FString& Input);

	// Your declarations go below!
	private:
	FString Hiddenword;
	int32 Lives;
	int16 Gamestate = 0;
	
	//TArray<FString> THiddenWords = {
	///* 3 */	TEXT("car"), TEXT("age"), TEXT("sea"), TEXT("bin"),
	///* 4 */	TEXT("want"), TEXT("fire"), TEXT("help"), TEXT("wise"), TEXT("your"), TEXT("home"), 
	///* 5 */	TEXT("unite"), TEXT("forum"), TEXT("place"), TEXT("horse"), 
	///* 6 */	TEXT("unwise"), TEXT("foster"), TEXT("forest"), TEXT("friend"), TEXT("pigeon")};
	
};
