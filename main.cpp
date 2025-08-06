#include "Includes/include.h"
#include "Includes/definition.h"

std::string getDayName() {
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    const char* weekday[] = { "Expires : " "Sunday,", "Monday,", "Tuesday,", "Wednesday,", "Thursday,", "Friday,", "Saturday," };
    return weekday[timeinfo->tm_wday];
}

std::string getAMPM() {
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    return (timeinfo->tm_hour < 12) ? "AM IST" : "PM IST";
}

void DrawHUD(AHUD *HUD) {
	
if (SilentCheatsEXP && g_LocalPlayer) {  // Only run when in actual match
    ImGui::GetIO().IniFilename = nullptr;   // Disable ImGui logs (anti-ban)
    ImGui::GetIO().LogFilename = nullptr;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    std::string dayName = getDayName();
    std::string ampm = getAMPM();

    if (!dayName.empty() && !ampm.empty()) {
        std::string datePart = dayName + " " + EXP + " " + ampm;

        ImVec2 pos = {
            (float) glWidth / 150.0f + glWidth / 34.9f, 
            680.0f
        };

        draw->AddText(
            nullptr,
            ((float) density / 12.0f),
            pos,
            IM_COL32(0, 255, 217, 255),
            datePart.c_str()
        );
    }
}

SilentCheatsEXP = true;


if (g_LocalPlayer) { // Only render in real match, not in lobby or logo
    draw->AddText(
        NULL,
        ((float) density / 13.0f),
        { (float) glWidth / 150 + glWidth / 1.2f, 680 },
        IM_COL32(255, 255, 0, 255),
        "Grave X Android (G v3.9.0)"
    );
}
/*
draw->AddText(NULL, ((float) density / 13.0f),{(float) glWidth / 150 + glWidth / 1.2f,680},IM_COL32(255, 255, 0, 255), 
       // "GraveCheats (BGMi - v3.9.0)"); */
				  
        auto Actors = GetActors();
        int totalEnemies = 0, totalBots = 0;

        ASTExtraPlayerCharacter *localPlayer = 0;
        ASTExtraPlayerController *localController = 0;
		
		
        for (int i = 0; i < Actors.size(); i++) {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerController::StaticClass())) {
                localController = (ASTExtraPlayerController *) Actor;
                break;
            }
        }

        if (localController) {
            for (int i = 0; i < Actors.size(); i++) {
                auto Actor = Actors[i];
                if (isObjectInvalid(Actor))
                    continue;

                if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                    if (((ASTExtraPlayerCharacter *) Actor)->PlayerKey ==
                        localController->PlayerKey) {
                        localPlayer = (ASTExtraPlayerCharacter *) Actor;
                        break;
                    }
                }
            }

            if (localPlayer) {
                    if (localPlayer->PartHitComponent) {
                        auto ConfigCollisionDistSqAngles = localPlayer->PartHitComponent->ConfigCollisionDistSqAngles;
                        for (int j = 0; j < ConfigCollisionDistSqAngles.Num(); j++) {
                            ConfigCollisionDistSqAngles[j].Angle = 180.0f;
                        }
                        localPlayer->PartHitComponent->ConfigCollisionDistSqAngles = ConfigCollisionDistSqAngles;
                    }
                    static bool bShooting = false;
                        if (LekhitTrack) {
                  
                        if (localPlayer->bIsWeaponFiring || localPlayer->bIsGunADS)
                        {
                            auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
                            if (WeaponManagerComponent)
                            {
                                auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
                                if ((int)propSlot.GetValue() >= 1 && (int)propSlot.GetValue() <= 3)
                                {
                                    auto CurrentWeaponReplicated = (ASTExtraShootWeapon *)WeaponManagerComponent->CurrentWeaponReplicated;
                                    if (CurrentWeaponReplicated)
                                    {
                                        auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
                                        if (ShootWeaponComponent)
                                        {
                                            int shoot_event_idx = 172;
                                            auto VTable = (void **)ShootWeaponComponent->VTable;
                                            auto f_mprotect = [](uintptr_t addr, size_t len,
                                                                 int32_t prot) -> int32_t
                                            {
                                                static_assert(PAGE_SIZE == 4096);
                                                constexpr size_t page_size = static_cast<size_t>(PAGE_SIZE);
                                                void *start = reinterpret_cast<void *>(addr & -page_size);
                                                uintptr_t end = (addr + len + page_size - 20) & -page_size;
                                                return mprotect(start, end - reinterpret_cast<uintptr_t>(start), prot);
                                            };
                                            if (VTable && (VTable[shoot_event_idx] != Hook_shoot_event))
                                            {
                                                Orig_Shoot_Event =
                                                    decltype(Orig_Shoot_Event)(VTable[shoot_event_idx]);

                                                f_mprotect((uintptr_t)(&VTable[shoot_event_idx]),
                                                           sizeof(uintptr_t), PROT_READ | PROT_WRITE);
                                                VTable[shoot_event_idx] = (void *)Hook_shoot_event;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    
                   }
					
    if (Lekhit::Esp::TargetLine) {
       ASTExtraPlayerCharacter *Target = GetTargetByPussy();              
       long PlayerAimLineColor = IM_COL32(225, 225, 255, 255); // White color              
       if (Target) {
       FVector RootPos = Target->GetBonePos("Root", {});
       ImVec2 RootPosSC;
       if (W2S(RootPos, (FVector2D *)&RootPosSC)) {
       draw->AddLine(RootPosSC, {(float) glWidth / 2, (float) glHeight}, PlayerAimLineColor, 0.4f); // Adjusted line width
          }
		}
				  								
				    if (Lekhit::AimBot::Enable) {
		  		    draw->AddCircle(ImVec2(glWidth / 2, glHeight / 2), Lekhit::AimBot::Cross, IM_COL32(255, 255, 255, 255), 0, 1.0f);
                    ASTExtraPlayerCharacter *Target = GetTargetForAimBot();
                    if (Target) {
                        bool triggerOk = true;
                        if (Lekhit::AimBot::Trigger != Lekhit::EAimTrigger::None) {
                            if (Lekhit::AimBot::Trigger == Lekhit::EAimTrigger::Shooting) {
                                triggerOk = localPlayer->bIsWeaponFiring;
                            } else if (Lekhit::AimBot::Trigger == Lekhit::EAimTrigger::Scoping) {
                                triggerOk = localPlayer->bIsGunADS;
                            } else if (Lekhit::AimBot::Trigger == Lekhit::EAimTrigger::Both) {
                                triggerOk = localPlayer->bIsWeaponFiring && localPlayer->bIsGunADS;
                            } else if (Lekhit::AimBot::Trigger == Lekhit::EAimTrigger::Any) {
                                triggerOk = localPlayer->bIsWeaponFiring || localPlayer->bIsGunADS;
                            }
                        } else triggerOk = true;
                        if (triggerOk) {
                            
                             FVector targetAimPos = Target->GetBonePos("Head", {});
                                targetAimPos.Z -= Lekhit::AimBot::Position;
                            
                            auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
                            if (WeaponManagerComponent) {
                                auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
                                if ((int) propSlot.GetValue() >= 1 &&
                                    (int) propSlot.GetValue() <= 3) {
                                    auto CurrentWeaponReplicated = (ASTExtraShootWeapon *) WeaponManagerComponent->CurrentWeaponReplicated;
                                    if (CurrentWeaponReplicated) {
                                        auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
                                        if (ShootWeaponComponent) {
                                            UShootWeaponEntity *ShootWeaponEntityComponent = ShootWeaponComponent->ShootWeaponEntityComponent;
                                            if (ShootWeaponEntityComponent) {
                                                ASTExtraVehicleBase *CurrentVehicle = Target->CurrentVehicle;
                                                if (CurrentVehicle) {
                                                    FVector LinearVelocity = CurrentVehicle->ReplicatedMovement.LinearVelocity;

                                                    float dist = localPlayer->GetDistanceTo(Target);
                                                    auto timeToTravel = dist /
                                                                        ShootWeaponEntityComponent->BulletFireSpeed;

                                                    targetAimPos = UKismetMathLibrary::Add_VectorVector(
                                                            targetAimPos,
                                                            UKismetMathLibrary::Multiply_VectorFloat(
                                                                    LinearVelocity, timeToTravel));
                                                } else {
                                                    FVector Velocity = Target->GetVelocity();

                                                    float dist = localPlayer->GetDistanceTo(Target);
                                                    auto timeToTravel = dist /
                                                                        ShootWeaponEntityComponent->BulletFireSpeed;

                                                    targetAimPos = UKismetMathLibrary::Add_VectorVector(
                                                            targetAimPos,
                                                            UKismetMathLibrary::Multiply_VectorFloat(
                                                                    Velocity, timeToTravel));
                                                }
                                                localController->SetControlRotation(ToRotator(
                                                        localController->PlayerCameraManager->CameraCache.POV.Location,
                                                        targetAimPos), "");
														
                                            if (Lekhit::AimBot::RecoilComparison) {
                                                    if (g_LocalPlayer->bIsGunADS) {
                                                        if (g_LocalPlayer->bIsWeaponFiring) {
                                                            float dist = g_LocalPlayer->GetDistanceTo(Target) / 100.f;                                                                                 
                                                            targetAimPos.Z -= dist * Lekhit::AimBot::Recc;
                                                        }  
                                                    }
                                                }
                                                localController->SetControlRotation(ToRotator(localController->PlayerCameraManager->CameraCache.POV.Location, targetAimPos), "");
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                  }
					
     
                if (localController != 0)
                {
                
                if (Lekhit::Memory::SmallCrossHair || Lekhit::Memory::FastShoot ||
                        Lekhit::Memory::NoRecoil || Lekhit::Memory::Instant) {
                        auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
                        if (WeaponManagerComponent) {
                            auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
                            if ((int) propSlot.GetValue() >= 1 && (int) propSlot.GetValue() <= 3) {
                                auto CurrentWeaponReplicated = (ASTExtraShootWeapon *) WeaponManagerComponent->CurrentWeaponReplicated;
                                if (CurrentWeaponReplicated) {
                                    auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
                                    if (ShootWeaponComponent) {
                                        UShootWeaponEntity *ShootWeaponEntityComponent = ShootWeaponComponent->ShootWeaponEntityComponent;
                                        if (ShootWeaponEntityComponent) {

                                            if (Lekhit::Memory::SmallCrossHair) {
                                                ShootWeaponEntityComponent->GameDeviationFactor = 0.0f;                                                
                                            }
                                            if (Lekhit::Memory::FastShoot) {
                                                ShootWeaponEntityComponent->ShootInterval = Lekhit::Memory::FastShoot;                                   
                                            }
                                            
											if (Lekhit::Memory::Instant) {
                                            }	
                                            
                                            if (Lekhit::Memory::NoRecoil) {
                                              ShootWeaponEntityComponent->RecoilKickADS = 0.0f;             // No Shake 1
                                              ShootWeaponEntityComponent->AnimationKick = 0.0f;             // No Shake 
                                              ShootWeaponEntityComponent->ShotGunCenterPerc = 0.0f;         // No Spread 1
                                              ShootWeaponEntityComponent->ShotGunVerticalSpread = 0.0f;     // No Spread 2
                                              ShootWeaponEntityComponent->ShotGunHorizontalSpread = 0.0f;   // No Spread 3
                                              ShootWeaponEntityComponent->AccessoriesVRecoilFactor = 0.0f;  // More Accuracy 1
                                              ShootWeaponEntityComponent->AccessoriesHRecoilFactor = 0.0f;  // More Accuracy 2
                                              ShootWeaponEntityComponent->AccessoriesRecoveryFactor = 0.0f; // More Accuracy 3

                                             }
                                           
                                           }
                                        }
                                    }
                                }
                            }
                        }
                              
                          for (auto &i : Actors) {
                           auto Actor = i;                
                           if (isObjectInvalid(Actor))
                            continue;
                            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {                                 
                            ImU32 PlayerBone;
                            ImU32 PlayerLine;
                            ImU32 BotLine;
                            ImU32 BotBone;
                            ImU32 PlayerAlert;
                            ImU32 BotAlert;
							ImU32 PlayerHealthColor;
							ImU32 PlayerBox;
                            auto Player = (ASTExtraPlayerCharacter *)Actor;
                            if(Player->bHidden)
                                continue;
                            bool IsVisible = localController->LineOfSightTo(Player, {0,0,0}, true);
                            if (IsVisible) {
                            BotBone = IM_COL32(0, 0, 0, 255);
                            PlayerBone = IM_COL32(0, 255, 195, 255);
                            PlayerLine = IM_COL32(0, 255, 195, 255);
                            BotLine = IM_COL32(0, 0, 0, 255);
                            PlayerBox = IM_COL32(255, 255, 255, 130);
                            PlayerHealthColor = IM_COL32(0, 255, 195, 255);
                            } else {
                            BotBone = IM_COL32(255, 255, 255, 255);
                            PlayerBone = IM_COL32(255, 0, 0, 255);
                            PlayerLine = IM_COL32(255, 0, 0, 255);
                            BotLine = IM_COL32(255, 255, 255, 255);
                            PlayerHealthColor = IM_COL32(0, 255, 195, 255);
						    }
                            float Distance = localPlayer->GetDistanceTo(Player) / 100.0f;
                            
                            if (Distance > 500.0f)                            
                                continue;
                                                        
                            if (Player->PlayerKey == localController->PlayerKey)                            
                                continue;                  

                            if (Player->TeamID == localController->TeamID)                            
                                continue;              
                                              
                            if (Player->bDead)                                    
                                continue;
                            
                            if(Player->bHidden)
                               continue;

                            if (Player->bEnsure)
                                totalBots++;
                            else
                                totalEnemies++;
                                                                
                            float magic_number = (Distance);
                            float mx = (glWidth / 4) / magic_number;

                            float healthLength = glWidth / 17;
                            if (healthLength < mx)
                                healthLength = mx;
                            auto HeadPos = Player->GetBonePos("Head", {});                            
                            ImVec2 headPosSC;


                            auto RootPos = Player->GetBonePos("Root", {});
                            ImVec2 RootPosSC;

                            if (W2S(HeadPos, (FVector2D *)&headPosSC) && W2S(RootPos, (FVector2D *)&RootPosSC))
                            {

                            if (Lekhit::Esp::Line) {
                            if (Player->bEnsure) {
                            draw->AddLine({(float) glWidth / 2, 80}, headPosSC, BotLine, 0.5f);
                            } else {
                            draw->AddLine({(float) glWidth / 2, 80}, headPosSC, PlayerLine, 0.5f);
                            }}
                                     

                                 if (Lekhit::Esp::Box) {
    float boxHeight = abs(headPosSC.y - RootPosSC.y) * 1.05f; 
    float boxWidth = boxHeight * 0.45f; 
    float borderThickness = 0.1f; 
    Box4Line(draw, borderThickness, headPosSC.x - (boxWidth / 2), headPosSC.y, boxWidth, boxHeight, PlayerBox);
}
								
                                        if (Lekhit::Esp::Skeleton) {
                                        static std::vector<std::string> right_arm{"neck_01",
                                                                              "clavicle_r",
                                                                              "upperarm_r",
                                                                              "lowerarm_r",
                                                                              "hand_r", "item_r"};
                                    static std::vector<std::string> left_arm{"neck_01",
                                                                             "clavicle_l",
                                                                             "upperarm_l",
                                                                             "lowerarm_l",
                                                                             "hand_l", "item_l"};
                                    static std::vector<std::string> spine{"Head", "neck_01",
                                                                          "spine_03",
                                                                          "spine_02", "spine_01",
                                                                          "pelvis"};
                                    static std::vector<std::string> lower_right{"pelvis", "thigh_r",
                                                                                "calf_r", "foot_r"};
                                    static std::vector<std::string> lower_left{"pelvis", "thigh_l",
                                                                               "calf_l", "foot_l"};
                                    static std::vector<std::vector<std::string>> skeleton{right_arm,
                                                                                          left_arm,
                                                                                          spine,
                                                                                          lower_right,
                                                                                          lower_left};
                                    for (auto &boneStructure: skeleton) {
                                        std::string lastBone;
                                        for (std::string &currentBone: boneStructure) {
                                            if (!lastBone.empty()) {
                                                ImVec2 boneFrom, boneTo;
                                                if (W2S(Player->GetBonePos(lastBone.c_str(), {}),
                                                        (FVector2D *) &boneFrom) &&
                                                        W2S(Player->GetBonePos(currentBone.c_str(), {}),
                                                            (FVector2D *) &boneTo)) {

                                                    if (Player->bEnsure) {
                                                        draw->AddLine(boneFrom, boneTo,
                                                                       BotBone, 0.5f);
                                                    } else {

                                                        draw->AddLine(boneFrom, boneTo,
                                                                      PlayerBone, 0.5f);
                                                    }
                                                }
                                            }
                                            lastBone = currentBone;
                                        }
                                    }
								}
								
                                if (Lekhit::Esp::TeamID || Lekhit::Esp::Name ||
                                    Lekhit::Esp::Distance) {
                                    ImGuiStyle &style = ImGui::GetStyle();
                                    ImVec4 savedTextColor = style.Colors[ImGuiCol_Text];
                                    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

                                    std::string s;

                                    if (Lekhit::Esp::TeamID) {
                                        s += "(" + std::to_string(Player->TeamID) + ") ";
                                    }

                                    if (Lekhit::Esp::Name) {
                                        s += Player->bEnsure ? "Bot"
                                                             : Player->PlayerName.ToString();
                                    }

                                    if (Lekhit::Esp::Distance) {
                                      float boxWidth = density / 1.6f;
                                    boxWidth -= std::min(((boxWidth / 2) / 00.0f) * Distance,boxWidth / 2);
                                    float boxHeight = boxWidth * 0.13f;
                                    std::string s;
							    	s += " ";
                                    s += std::to_string((int) Distance);
                                    s += " M";
                                    auto textSize = ImGui::CalcTextSize(s.c_str(), 0, ((float) density / 15.0f)); 	//17 for me					
                                    float strokeSize = 1.5f;
                                    for (float x = -strokeSize; x <= strokeSize; x += strokeSize) {
                                    for (float y = -strokeSize;
                                    y <= strokeSize; y += strokeSize) {
                                    }
                                    }
                                    draw->AddText(NULL, ((float) density / 15.0f),{RootPosSC.x - (textSize.x / 2), RootPosSC.y},IM_COL32(255, 255, 255, 255), s.c_str());
                                    style.Colors[ImGuiCol_Text] = savedTextColor;//density / 15.f) for me
                                    }}												

                                    if (Lekhit::Esp::Health) {  
         
                                    int CurHP = (int) std::max(0, std::min((int) Player->Health,100));
         int MaxHP = 100;
         
               long HPColor;
                                    if (Player->Health < 50)
                                         HPColor = IM_COL32(255, 0, 0, 255);
                                     else if (Player->Health < 75)
                                         HPColor = IM_COL32(255, 255, 0, 255);
                                     else if ( Player->Health < 90)
                                         HPColor = IM_COL32(0, 255, 195, 255);
                                     else
                                        HPColor = PlayerHealthColor;
                
                                    if (Player->Health == 0.0f && !Player->bDead) {
                                        HPColor = IM_COL32(255, 0, 0, 255);

                                        CurHP = Player->NearDeathBreath;
                                        if (Player->NearDeatchComponent) {
                                            MaxHP = Player->NearDeatchComponent->BreathMax;
                                        }
                                    }
         
         if (Player->bEnsure) {
         BotBone = IM_COL32(0, 0, 0, 255);
         HPColor = IM_COL32(0, 0, 0, 255);
         
                                    float boxWidth = density / 6.0f;
                                    boxWidth -= std::min(((boxWidth / 2) / 700.0f) * Distance, boxWidth / 2);
                                    float boxHeight = boxWidth * 0.11f;
         boxWidth += 7.0f;  // Increase boxWidth by 50 units (for example)

                                    ImVec2 vStart = {headPosSC.x - (boxWidth / 2), headPosSC.y - (boxHeight * 1.5f)};
                                    ImVec2 vEndFilled = {vStart.x + (CurHP * boxWidth / MaxHP), vStart.y + boxHeight};
                                    ImVec2 vEndRect = {vStart.x + boxWidth, vStart.y + boxHeight};

                                    draw->AddRectFilled(vStart, vEndFilled, HPColor, 2.0f);
                                    draw->AddRect(vStart, vEndRect, IM_COL32(255, 255, 255, 255), 1.0f);//totalBots Coding
         } 
         else 
         {  
                                    float boxWidth = density / 6.0f;
                                    boxWidth -= std::min(((boxWidth / 2) / 700.0f) * Distance, boxWidth / 2);
                                    float boxHeight = boxWidth * 0.11f;
         boxWidth += 7.0f;  // Increase boxWidth by 50 units (for example)

                                    ImVec2 vStart = {headPosSC.x - (boxWidth / 2), headPosSC.y - (boxHeight * 1.5f)};
                                    ImVec2 vEndFilled = {vStart.x + (CurHP * boxWidth / MaxHP), vStart.y + boxHeight};
                                    ImVec2 vEndRect = {vStart.x + boxWidth, vStart.y + boxHeight};

                                    draw->AddRectFilled(vStart, vEndFilled, HPColor, 1.0f);
                                    draw->AddRect(vStart, vEndRect, IM_COL32(0,0,0,100), 1.0f);//totalEnemies Coding
         }}}

                               if (Lekhit::Esp::Alert) {
                                bool shit = false;

                                FVector MyPosition, EnemyPosition;
                                ASTExtraVehicleBase *CurrentVehiclea = Player->CurrentVehicle;
                                if (CurrentVehiclea) {
                                    MyPosition = CurrentVehiclea->RootComponent->RelativeLocation;
                                } else {
                                    MyPosition = Player->RootComponent->RelativeLocation;
                                }
                                ASTExtraVehicleBase *CurrentVehicle = localPlayer->CurrentVehicle;
                                if (CurrentVehicle) {
                                    EnemyPosition = CurrentVehicle->RootComponent->RelativeLocation;
                                } else {
                                    EnemyPosition = localPlayer->RootComponent->RelativeLocation;
                                }
                                FVector EntityPos = WorldToRadar(
                                        localController->PlayerCameraManager->CameraCache.POV.Rotation.Yaw,
                                        MyPosition, EnemyPosition, NULL, NULL,
                                        Vector3(glWidth, glHeight, 0), shit);
                                FVector angle = FVector();
                                Vector3 forward = Vector3((float) (glWidth / 2) - EntityPos.X,
                                                          (float) (glHeight / 2) - EntityPos.Y,
                                                          0.0f);
                                VectorAnglesRadar(forward, angle);
                                const auto angle_yaw_rad = DEG2RAD(angle.Y + 180.f);
                                const auto new_point_x = (glWidth / 2) +
                                                         (30 /*alert dist from me*/) / 2 * 8 *
                                                         cosf(angle_yaw_rad);
                                const auto new_point_y = (glHeight / 2) +
                                                         (30 /*alert dist from me*/) / 2 * 8 *
                                                         sinf(angle_yaw_rad);
                                std::array<Vector3, 3> points{
                                        Vector3(new_point_x - ((90) / 4 + 3.5f) / 2,
                                                new_point_y - ((30) / 4 + 3.5f) / 2, 0.f),
                                        Vector3(new_point_x + ((90) / 4 + 3.5f) / 4, new_point_y,
                                                0.f), Vector3(new_point_x - ((30) / 4 + 3.5f) / 2,
                                                              new_point_y + ((20) / 4 + 3.5f) / 2,
                                                              0.f)};
                                RotateTriangle(points, angle.Y + 180.0f);
                                int TeamId = Player->TeamID;
                                TeamColor teamColor = GetColorForTeam(TeamId);
                                ImU32 imColor = IM_COL32(teamColor.r, teamColor.g, teamColor.b,
                                                         255); // Convert TeamColor to ImU32
                                draw->AddCircle(ImVec2(new_point_x, new_point_y), 5.0f, imColor, 64,
                                                5.0f);
                                }}
						
					        	if (Lekhit::Memory::Information) {         
                                if (Actor->IsA(ASTExtraGameStateBase::StaticClass())) {
                                auto InGame = (ASTExtraGameStateBase *) Actor;
                                std::string s;
                                std::string Info;
                                Info += "Telegram Channel :";
                                Info += "Shaykmodz";
                                Info += "\nMatch ID : ";
                                Info += std::to_string((int) InGame->GameID);
                                Info += "\nTeam Mode: ";
                                Info += std::to_string((int) InGame->PlayerNumPerTeam);
                                s += "\nTotal Alive Players: " ;
                                s += std::to_string((int) InGame->AlivePlayerNum);
                                s += "\nReal Players: ";
                                s += std::to_string((int) InGame->PlayerNum);
                                s += "\nTeam Remaining: ";
                                s += std::to_string((int) InGame->AliveTeamNum);
                                s += "\nMatch Time  : ";
                                s += std::to_string((int) InGame->ElapsedTime);
                                s += "s | ";
                                s += std::to_string((int) InGame->ElapsedTime / 60);
                                s += "m";
                  
                                draw->AddText(NULL, ((float) density / 25.f), ImVec2(glWidth / 2.1 - 650.f, 550), IM_COL32(255, 255, 255, 255), s.c_str());
                                draw->AddText(NULL, ((float) density / 25.f), ImVec2(glWidth / 2.1 - 650.f, 500), IM_COL32(255, 255, 255, 255), Info.c_str());
                              draw->AddRectFilled(ImVec2(glWidth / 2 - 700.f, 490), ImVec2(glWidth / 2 - 480.f, 650), IM_COL32(0, 0, 0, 0), 15.0f);
                             }
                           }
						
                    if (Lekhit::Esp::Vehicle::Name || Lekhit::Esp::Vehicle::Fuel || Lekhit::Esp::Vehicle::Health)
                    {
                        if (i->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *) i;
                            if (!Vehicle->Mesh)
                                continue;
                                
                            int CurHP = (int) std::max(0, std::min((int) Vehicle->VehicleCommon->HP, (int) Vehicle->VehicleCommon->HPMax));
                            int MaxHP = (int) Vehicle->VehicleCommon->HPMax;
                            long curHP_Color = IM_COL32(std::min(((510 * (MaxHP - CurHP)) / MaxHP), 255), std::min(((510 * CurHP) / MaxHP), 255), 0, 155);
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;
                            FVector2D vehiclePos;
                            if (W2S(Vehicle->K2_GetActorLocation(), &vehiclePos))
                            {                            
                                auto mWidthScale = std::min(0.10f * Distance, 50.f);
                                auto mWidth = 70.f - mWidthScale;
                                auto mHeight = mWidth * 0.15f;
                                if (Lekhit::Esp::Vehicle::Name) {
                                    std::string s = GetVehicleName(Vehicle);
                                    s += " (";
                                    s += std::to_string((int)Distance);
                                    s += " M)";
                                    draw->AddText(NULL, ((float)density / 20.0f), {vehiclePos.X - (mWidth / 2), vehiclePos.Y}, IM_COL32(255, 255, 0, 255), s.c_str());
                                }   //20 density for me only
                                    if (Lekhit::Esp::Vehicle::Fuel) {
                                    std::string sf;
                                    sf +=  " FUEL : ";
                                    sf += std::to_string((int)(100 * Vehicle->VehicleCommon->Fuel / Vehicle->VehicleCommon->FuelMax));
                                    sf += "";
                                    draw->AddText(NULL, ((float)density / 30.0f), {vehiclePos.X - (mWidth / 2), vehiclePos.Y + 15.f}, IM_COL32(255, 255, 0, 255), sf.c_str());
                                }
                                    if (Lekhit::Esp::Vehicle::Health) {
                                    ImVec2 vStart = {vehiclePos.X - (mWidth / 2), vehiclePos.Y - (mHeight * 1.5f)};
                                    ImVec2 vEndFilled = {vStart.x + (CurHP * mWidth / MaxHP), vStart.y + mHeight};
                                    ImVec2 vEndRect = {vStart.x + mWidth, vStart.y + mHeight};
                                    draw->AddRectFilled(vStart, vEndFilled, curHP_Color, 3.2f, 240);
                                    draw->AddRect(vStart, vEndRect, IM_COL32(000, 000, 000, 255), 3.2f, 240);
                                    }
                                }
                            }
                        }                                
                    }
                }
            }
        }
    }
	
	
	char extra[32];
g_LocalController = localController;
g_LocalPlayer = localPlayer;
if (totalEnemies > 0 || totalBots > 0) {
    auto draw = ImGui::GetForegroundDrawList();
    float centerX = glWidth / 2.0f;

    // Background Boxes (rounded corners and smooth alpha)
    draw->AddRectFilled({centerX - 42, 44}, {centerX, 82}, ImColor(10, 173, 255, 170), 6.0f);  // Enemies
    draw->AddRectFilled({centerX + 1, 44}, {centerX + 43, 82}, ImColor(0, 0, 0, 170), 6.0f);    // Bots

    // Draw Borders (HD outlines)
    draw->AddRect({centerX - 42, 44}, {centerX, 82}, ImColor(255, 255, 255, 30), 1.5f, 0, 2.0f);
    draw->AddRect({centerX + 1, 44}, {centerX + 43, 82}, ImColor(255, 255, 255, 30), 1.5f, 0, 2.0f);

    // Enemies Count Text
    sprintf(extra, "%d", totalEnemies);
    draw->AddText(ImVec2(centerX - 30, 52), ImColor(255, 255, 255, 255), extra);

    // Bots Count Text
    sprintf(extra, u8"%d", totalBots);
    draw->AddText(ImVec2(centerX + 11, 52), ImColor(255, 255, 255, 255), extra);
}}
	
	
       /* char extra[32];
        g_LocalController = localController;
        g_LocalPlayer = localPlayer;
        if (totalEnemies > 0 || totalBots > 0) {
        ImGui::GetForegroundDrawList()->AddRectFilled({glWidth /2-38,47},{glWidth /2,80},ImColor(10,173,255,110));
        ImGui::GetForegroundDrawList()->AddRectFilled({glWidth /2+38,47},{glWidth /2,80},ImColor(0,0,0,110));
        sprintf(extra, "%d", totalEnemies);
        ImGui::GetForegroundDrawList()->AddText({glWidth /2-26,47}, ImColor(255,255,255,255), extra);
        sprintf(extra, u8"%d", totalBots);
        ImGui::GetForegroundDrawList()->AddText({glWidth /2+13,47}, ImColor(255,255,255,255), extra);
        }}*/

EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean _eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);

    if (glWidth <= 0 || glHeight <= 0)
        return orig_eglSwapBuffers(dpy, surface);

    if (!g_App)
        return orig_eglSwapBuffers(dpy, surface);

    screenWidth = ANativeWindow_getWidth(g_App->window);
    screenHeight = ANativeWindow_getHeight(g_App->window);
    density = AConfiguration_getDensity(g_App->config);

    if (!initImGui) {
        ImGui::CreateContext();
        ImGuiStyle &style = ImGui::GetStyle();
        ImGui::StyleColorsDark();
        ImGui::GetStyle().AntiAliasedLines = true;
        ImGui::GetStyle().AntiAliasedFill = true;
        style.WindowPadding = ImVec2(7, 7);
        style.WindowRounding = 0.0f;
        style.FramePadding = ImVec2(4, 4);
        style.FrameRounding = 5.5f;
        style.FrameBorderSize = 1.0f;
        style.WindowBorderSize = 0.0f;
        ImGui_ImplAndroid_Init();
        ImGui_ImplOpenGL3_Init("#version 300 es");
        ImGuiIO &io = ImGui::GetIO();
        io.Fonts->AddFontFromMemoryTTF((void *) PIRO_data, PIRO_size, 27.0f, NULL,
                                       io.Fonts->GetGlyphRangesDefault());
        ImFontConfig cfg;
        cfg.SizePixels = ((float) density / 20.0f);
        io.Fonts->AddFontDefault(&cfg);
        initImGui = true;
    }

    ImGuiIO &io = ImGui::GetIO();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
    ImGui::NewFrame();

    DrawESP(ImGui::GetBackgroundDrawList());

    ImGui::SetNextWindowSize(ImVec2((float) glWidth * 0.42f, (float) glHeight * 0.52f),
                             ImGuiCond_Once);
            char buf[128];
            static bool isLogin = false;
            static std::string err;
            if (!isLogin) {
            static char s[64];
            ImGui::InputText("##key", s, sizeof s);
            auto key = getClipboardText();
            strncpy(s, key.c_str(), sizeof s);
            err = Login(s);
            if (err == "OK") {
                isLogin = bValid && g_Auth == g_Token;
            }
            if (err != "OK") {
                abort();
            }
               } else {
	        Lekhit::Esp::Line = true;
			Lekhit::Esp::Box = true;	
			Lekhit::Esp::Health = true;
			Lekhit::Esp::Skeleton = true;		
			Lekhit::Esp::Distance = true;
		    Lekhit::Esp::Vehicle::Name = true;
			Lekhit::LekhitTrack::IgnoreKnock = true;
			Lekhit::LekhitTrack::Enable = true;
			Lekhit::LekhitTrack::VisCheck = true;
		    //Lekhit::Memory::SmallCrossHair = true; 
			//Lekhit::Memory::CheatBypass = true; 
    }
    ImGui::End();
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return orig_eglSwapBuffers(dpy, surface);
}

#define SLEEP_TIME 1000LL / 120LL
void *ipad_thread(void *) {
        while (true) {
        auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        if (Lekhit::Memory::WideView) {
        auto objs = UObject::GetGlobalObjects();
        for (int i = 0; i < objs.Num(); i++) {
        auto Object = objs.GetByIndex(i);
        if (isObjectInvalid(Object))
                continue;
          if (Object->IsA(ULocalPlayer::StaticClass())) {
          auto playerChar = (ULocalPlayer *) Object;      
          playerChar->AspectRatioAxisConstraint = EAspectRatioAxisConstraint::AspectRatio_MaintainYFOV;
     }     
     }
     }
         auto td = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - t1;
         std::this_thread::sleep_for(std::chrono::milliseconds(std::max(std::min(0LL, SLEEP_TIME - td),SLEEP_TIME)));
     }  
  }
  
 void FixGameCrash()
        {
        system("rm -rf /data/data/com.pubg.imobile/files");
        system("rm -rf /data/data/com.pubg.imobile/files/ano_tmp");
        system("touch /data/data/com.pubg.imobile/files/ano_tmp");
        system("chmod 000 /data/data/com.pubg.imobile/files/ano_tmp");
        system("rm -rf /data/data/com.pubg.imobile/files/obblib");
        system("touch /data/data/com.pubg.imobile/files/obblib");
        system("chmod 000 /data/data/com.pubg.imobile/files/obblib");
        system("rm -rf /data/data/com.pubg.imobile/files/xlog");
        system("touch /data/data/com.pubg.imobile/files/xlog");
        system("chmod 000 /data/data/com.pubg.imobile/files/xlog");
        system("rm -rf /data/data/com.pubg.imobile/app_bugly");
        system("touch /data/data/com.pubg.imobile/app_bugly");
        system("chmod 000 /data/data/com.pubg.imobile/app_bugly");
        system("rm -rf /data/data/com.pubg.imobile/app_crashrecord");
        system("touch /data/data/com.pubg.imobile/app_crashrecord");
        system("chmod 000 /data/data/com.pubg.imobile/app_crashrecord");
        system("rm -rf /data/data/com.pubg.imobile/app_crashSight");
        system("touch /data/data/com.pubg.imobile/app_crashSight");
        system("chmod 000 /data/data/com.pubg.imobile/app_crashSight");
}
		
void *main_thread(void *) {
	FixGameCrash();
    Lekhit::libUE4Base = Tools::GetBaseAddress("libUE4.so");
    while (!Lekhit::libUE4Base) {
        Lekhit::libUE4Base = Tools::GetBaseAddress("libUE4.so");
        sleep(1);
    }
	
	Lekhit::libanogsBase = Tools::GetBaseAddress("libanogs.so");
    while (!Lekhit::libanogsBase) {
        Lekhit::libanogsBase = Tools::GetBaseAddress("libanogs.so");
        sleep(1);
    }

   // MemoryPatch::createWithHex("libanogs.so", 0x139270, "00 00 80 D2 C0 03 5F D6").Modify(); // .ioctl
   // MemoryPatch::createWithHex("libanogs.so", 0x139260, "00 00 80 D2 C0 03 5F D6").Modify(); // ferror offline

    while (!g_App) {
        g_App = *(android_app * *)(Lekhit::libUE4Base + Lekhit::GNativeAndroidApp_Offset);
        sleep(1);
    }

    FName::GNames = GetGNames();
    while (!FName::GNames) {
        FName::GNames = GetGNames();
        sleep(1);
    }
    UObject::GUObjectArray = (FUObjectArray * )(Lekhit::libUE4Base + Lekhit::GUObject_Offset);

    orig_onInputEvent = decltype(orig_onInputEvent)(g_App->onInputEvent);
    g_App->onInputEvent = onInputEvent;
    initOffset();
	
	Tools::Hook((void *) 
	DobbySymbolResolver(OBFUSCATE("libRSDriver.so"), 
	OBFUSCATE("eglSwapBuffers")), 
	(void *) _eglSwapBuffers, 
	(void **) &orig_eglSwapBuffers);
	
    return nullptr;
}

__attribute__((constructor)) void _init() {

    pthread_create(&t, NULL, main_thread, NULL); 
	pthread_create(&t, NULL, ipad_thread, NULL);
}
