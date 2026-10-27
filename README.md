# BLACK OCEAN

**Modern Naval Strategy · Tactical Fleet Command · Open-World Maritime Simulation**
Built with Unreal Engine 5 + C++ — fully fictional nations, vessels and organizations.

---

# English

## Overview

BLACK OCEAN puts the player in command of a fictional naval fleet, managing
naval operations, navigation, reconnaissance, fleet logistics, maritime
economy, port and shipyard management, research, diplomacy and long-term
strategic decisions across a persistent, living ocean world. All countries,
vessels, weapons, sensors, bases and organizations depicted are entirely
fictional and are not modeled on any real-world military system.

Core simulation systems (ocean/weather, fleet command, sensors, damage,
crew, logistics, economy, diplomacy, AI, save/replay) are written in C++.
Blueprint is reserved for level composition, animation, UI binding, VFX and
designer iteration.

## Key Features

**World & Ocean**
- Global Maritime Simulation Engine: per-region depth, temperature, current,
  wave height, visibility, weather, traffic density, resources and threat
  level, all affecting movement, detection, communication and missions.
- Dynamic ocean/weather drift with storm seeding, day/night cycle support.

**Fleet, Ships & Crew**
- Thirteen fictional vessel classes (Command Ship, Frigate-like, Destroyer-
  like, Cruiser-like, Carrier-like Platform, Submarine, Corvette, Patrol
  Craft, Amphibious Support, Logistics Ship, Research Vessel, Rescue Vessel,
  Drone Carrier), each with independent mobility, sensors, crew, fuel,
  maintenance, storage, communications and mission role.
- Twelve independently-failable ship systems (Hull, Engine, Power,
  Propulsion, Sensors, Comms, Navigation, Flight Deck, Internal Systems,
  Cooling, Cargo, Mission Modules) with a damage/repair/isolation loop
  (flooding, fire, power/engine failure, sensor/comm loss, mobility loss).
- Crew simulation with Experience, Fatigue, Skill, Morale and Workload per
  role (Captain, Engineer, Navigator, Sensor Operator, Comms Officer,
  Flight Crew, Support Team), plus officer-to-officer relationships (Trust,
  Cooperation, Rivalry, Loyalty) that affect shared-task efficiency.
- Fictional, gameplay-only submarine loop: depth, buoyancy-by-mode, battery,
  oxygen, hull integrity and noise signature.

**Sensors, Command & AI**
- Multi-sensor fusion (radar-like, sonar, optical, infrared-like, passive
  acoustic, drone, satellite-style feed, human report) producing confidence-
  weighted contact classification (Unknown/Civilian/Friendly/Neutral/
  Suspicious/Hostile) that decays without refresh — AI only ever acts on
  what has actually been sensed.
- Fleet → Task Force → Squadron → Group → Vessel command hierarchy, with
  orders (Move, Patrol, Escort, Recon, Search, Rescue, Rendezvous, Hold,
  Return to Port, Support, Supply) delayed realistically by distance and
  communication reliability.
- Faction-level AI (doctrine, risk tolerance, economic/military priority)
  and per-fleet AI (patrol/recon/escort/search/retreat/resupply/repair)
  that reason only over detected contacts, never hidden ground truth.

**Economy, Logistics & Diplomacy**
- National budget allocation across Navy, Research, Infrastructure,
  Logistics, Industry, Environment and Emergency Reserve, with a computed
  financial-pressure score that should visibly constrain fleet size and
  readiness.
- Supply-chain routes moving Fuel, Spare Parts, Food, Medical Supplies,
  Ammunition-equivalent resources, Components and Maintenance Materials,
  with congestion, weather risk and interruption modeling.
- Ports with configurable Dock Capacity, Repair Capacity, Fuel Reserve,
  Storage, Shipyard presence, Trade Volume and Security Level — **including
  a player-configurable operating-hours schedule** showing live status
  ("Open — closes in 3h 20m" / "Closed — opens in 0h 45m") for any window
  the player sets, or 24-hour operation.
- Research tree (Sensors, Propulsion, Comms, Automation, Materials, Energy
  Storage, Underwater Systems, Recon, Drones, Ship Design, Logistics,
  Damage Control) gated by prerequisites, time and budget.
- Bilateral diplomacy (relation score, Trade/Port Access/Intelligence
  Sharing/Research Cooperation/Navigation Rights/Search & Rescue treaties)
  gated by trust thresholds per treaty type.

**Missions, Save, Replay & Tooling**
- Dynamic, dependency-gated mission objectives (Pending → Active →
  Completed/Failed/Recovery/Alternative Success) driven by world state
  rather than a fixed script.
- Branching dialogue graph data structures for captains, scientists,
  engineers, diplomats and commanders.
- Deterministic campaign clock (Pause/1x/2x/5x/10x/25x) so recorded replays
  and automated scenario tests reproduce exactly.
- Versioned multi-slot save system with checksum integrity validation and
  autosave, ready for crash recovery.
- Content Validation Tool (duplicate IDs, missing localization, and hooks
  for broken-scenario/route/dialogue checks) intended to run in CI before
  every package.

**UI, Themes & Accessibility**
- Six runtime-switchable UI themes: **Windows 11-inspired default, Dark
  Navy, Light, Ocean Blue/Cyan, Red Alert, High Contrast.**
- Full English / Persian / Chinese localization with automatic **Right-to-
  Left flow for Persian** and Left-to-Right for English/Chinese, string-
  table fallback (missing translation → English → raw key, never blank),
  and font-scale/colorblind/reduced-motion accessibility hooks.

## Tech Stack

| Layer | Technology |
|---|---|
| Engine | Unreal Engine 5 (5.3 / 5.4 / 5.5) |
| Core simulation | C++ |
| Level/UI/VFX authoring | Blueprint (added in-editor) |
| UI framework | UMG / CommonUI |
| Data | Data Tables, JSON string tables |
| Build | UnrealBuildTool, RunUAT, PowerShell automation |

## Project Structure

```
BlackOcean.uproject
Source/BlackOcean/
  Core/          Simulation/     Ocean/         Ships/
  Submarine/     AirAssets/      Crew/          Sensors/
  Navigation/    Fleet/          Command/       AI/
  Logistics/     Ports/          Shipyard/      Research/
  Economy/       Diplomacy/      Missions/      Dialogue/
  Save/          Replay/         UI/            Networking/
  Tools/
Content/         Maps, Ocean, Ships, Vehicles, AI, Data, UI/Themes,
                 Audio, VFX, Missions, Scenarios, Localization/{en,fa,zh}
Plugins/         (reserved for future per-system plugins)
Tests/           Automation test examples
Scripts/         setup-windows.ps1, build-development.ps1,
                 build-shipping.ps1, run-tests.ps1, package.ps1, clean.ps1
Config/          DefaultEngine.ini, DefaultGame.ini, DefaultInput.ini
Docs/            GDD.md, TechnicalDesign.md, ModdingGuide.md,
                 LocalizationGuide.md, BuildGuide.md
INSTALLATION.md
```

## Requirements (Windows 10/11)

- **Epic Games Launcher** — https://store.epicgames.com/download
- **Unreal Engine 5** (5.3/5.4/5.5) — installed via the launcher
- **Visual Studio 2022** with the **Desktop development with C++** and
  **Game development with C++** workloads (installs the Windows SDK)
- **Git** — https://git-scm.com/download/win

## Installation & Build

1. Install every item under **Requirements** above.
2. Open PowerShell in the `Scripts/` folder and run:
   ```powershell
   ./setup-windows.ps1
   ```
   This checks Git, Visual Studio + C++ tools, the Windows SDK and Unreal
   Engine 5, and reports anything missing.
3. Generate project files and build the Development Editor:
   ```powershell
   ./build-development.ps1
   ```
4. Open `BlackOcean.uproject` to launch the Editor.
5. Run the automation test suite:
   ```powershell
   ./run-tests.ps1
   ```
6. Build a Shipping configuration:
   ```powershell
   ./build-shipping.ps1
   ```
7. Package a distributable build:
   ```powershell
   ./package.ps1
   ```
8. Clean intermediate/build files at any time:
   ```powershell
   ./clean.ps1
   ```

Full step-by-step detail (including troubleshooting) is in `INSTALLATION.md`.

## Scope Note

This repository is a **systems foundation**: the core gameplay systems above
are implemented with real, working C++ logic and a professional project
structure, ready to extend. A complete AAA-scale release — full 3D art,
voice-over, hundreds of hours of scripted campaign content, and a shipped
multiplayer layer — is a multi-year, studio-scale undertaking that no single
delivery can produce in full; the Networking module is deliberately an
interface-only seam for that future work rather than a finished
implementation.

---

# فارسی

## معرفی

**بلک اوشن (BLACK OCEAN)** بازیکن را در جایگاه فرمانده یک ناوگان دریایی
کاملاً خیالی قرار می‌دهد که باید هم‌زمان عملیات دریایی، ناوبری، شناسایی،
لجستیک ناوگان، اقتصاد دریایی، مدیریت بندر و تعمیرگاه کشتی، تحقیق و توسعه،
دیپلماسی و تصمیم‌گیری‌های راهبردی بلندمدت را در یک جهان اقیانوسی پایدار و
زنده مدیریت کند. تمام کشورها، ناوها، سلاح‌ها، حسگرها، پایگاه‌ها و سازمان‌های
نمایش داده‌شده کاملاً خیالی هستند و بر اساس هیچ سیستم نظامی واقعی طراحی
نشده‌اند.

هسته‌های اصلی شبیه‌سازی (اقیانوس/آب‌وهوا، فرماندهی ناوگان، حسگرها، آسیب،
خدمه، لجستیک، اقتصاد، دیپلماسی، هوش مصنوعی، ذخیره/بازپخش) با **C++** نوشته
شده‌اند و Blueprint صرفاً برای چیدمان مرحله، انیمیشن، اتصال رابط کاربری،
جلوه‌های ویژه و کار سریع طراحان در نظر گرفته شده است.

## ویژگی‌های کلیدی

**جهان و اقیانوس**
- موتور شبیه‌سازی دریایی سراسری: برای هر منطقه، عمق، دما، جریان، ارتفاع
  موج، دید، آب‌وهوا، تراکم ترافیک، منابع و سطح تهدید ثبت و روی حرکت، شناسایی،
  ارتباطات و مأموریت‌ها اثر می‌گذارد.
- تغییر پویای اقیانوس/آب‌وهوا با امکان ایجاد طوفان و چرخه شب و روز.

**ناوگان، کشتی‌ها و خدمه**
- سیزده کلاس شناور خیالی (کشتی فرماندهی، فریگیت‌گونه، ناوشکن‌گونه،
  رزم‌ناو‌گونه، سکوی هواپیمابر‌گونه، زیردریایی، کاروت، ناو گشتی، پشتیبانی
  آبی‌خاکی، کشتی لجستیک، کشتی تحقیقاتی، کشتی نجات، حامل پهپاد) با تحرک،
  ظرفیت حسگر، خدمه، سوخت، نگهداری، انبار، ارتباطات و نقش مأموریت مستقل.
- دوازده سامانه مستقل و قابل خرابی در هر کشتی (بدنه، موتور، تولید قدرت،
  رانش، حسگرها، ارتباطات، ناوبری، عرشه پرواز، سامانه‌های داخلی، خنک‌کننده،
  محفظه بار، ماژول‌های مأموریت) همراه با چرخه آسیب/تعمیر/ایزوله‌سازی
  (آب‌گرفتگی، آتش‌سوزی، قطع برق/موتور، از کار افتادن حسگر/ارتباطات، کاهش
  تحرک).
- شبیه‌سازی خدمه با تجربه، خستگی، مهارت، روحیه و حجم کار برای هر نقش
  (فرمانده، مهندس، ناوبر، اپراتور حسگر، افسر ارتباطات، خدمه پروازی، تیم
  پشتیبانی)، به‌همراه روابط افسران (اعتماد، همکاری، رقابت، وفاداری) که بر
  کارایی وظایف مشترک اثر می‌گذارد.
- چرخه زیردریایی کاملاً بازی‌محور و خیالی: عمق، شناوری بر اساس حالت، باتری،
  اکسیژن، یکپارچگی بدنه و امضای صوتی.

**حسگرها، فرماندهی و هوش مصنوعی**
- ترکیب چند حسگره (راداری، سونار، دوربین نوری، مادون‌قرمز‌گونه، آکوستیک
  غیرفعال، پهپاد شناسایی، فید ماهواره‌ای‌گونه، گزارش انسانی) که یک
  طبقه‌بندی مبتنی بر اطمینان (نامشخص/غیرنظامی/خودی/بی‌طرف/مشکوک/متخاصم)
  تولید می‌کند و بدون به‌روزرسانی، به‌مرور کاهش می‌یابد — هوش مصنوعی فقط بر
  اساس آنچه واقعاً شناسایی شده تصمیم می‌گیرد.
- ساختار فرماندهی ناوگان ← نیروی ضربت ← اسکادران ← گروه ← شناور، با دستورات
  (حرکت، گشت‌زنی، اسکورت، شناسایی، جست‌وجو، نجات، محل تلاقی، توقف، بازگشت به
  بندر، پشتیبانی، تدارکات) که بر اساس فاصله و قابلیت اطمینان ارتباطات با
  تأخیر واقع‌گرایانه اجرا می‌شوند.
- هوش مصنوعی سطح کشور/سازمان (اصول، ریسک‌پذیری، اولویت اقتصادی/نظامی) و هوش
  مصنوعی سطح ناوگان (گشت/شناسایی/اسکورت/جست‌وجو/عقب‌نشینی/تأمین مجدد/تعمیر)
  که فقط بر اساس Contactهای شناسایی‌شده تصمیم می‌گیرند، نه اطلاعات پنهان.

**اقتصاد، لجستیک و دیپلماسی**
- تخصیص بودجه ملی میان نیروی دریایی، تحقیقات، زیرساخت، لجستیک، صنعت، محیط
  زیست و ذخیره اضطراری، همراه با شاخص فشار مالی که باید به‌وضوح روی اندازه و
  آمادگی ناوگان اثر بگذارد.
- مسیرهای زنجیره تأمین برای انتقال سوخت، قطعات یدکی، غذا، ملزومات پزشکی،
  منابع معادل مهمات، اجزا و مواد نگهداری، با مدل‌سازی تراکم، ریسک آب‌وهوایی
  و اختلال.
- بنادر با ظرفیت اسکله، ظرفیت تعمیر، ذخیره سوخت، انبار، وجود تعمیرگاه کشتی،
  حجم تجارت و سطح امنیت قابل تنظیم — **از جمله یک برنامه ساعات کاری کاملاً
  قابل تنظیم توسط بازیکن** که وضعیت زنده بندر را نشان می‌دهد
  («باز — تا ۳ ساعت و ۲۰ دقیقه دیگر بسته می‌شود» یا «بسته — تا ۰ ساعت و ۴۵
  دقیقه دیگر باز می‌شود»)، برای هر بازه‌ای که بازیکن تعیین کند، یا حالت
  ۲۴ ساعته.
- درخت فناوری (حسگرها، رانش، ارتباطات، اتوماسیون، مواد، ذخیره‌سازی انرژی،
  سامانه‌های زیرآبی، شناسایی، پهپادها، طراحی کشتی، لجستیک، کنترل آسیب) که
  مشروط به پیش‌نیاز، زمان و بودجه است.
- دیپلماسی دوجانبه (امتیاز روابط، معاهدات تجاری/دسترسی به بندر/تبادل
  اطلاعات/همکاری تحقیقاتی/حق ناوبری/جست‌وجو و نجات) که مشروط به آستانه
  اعتماد هر نوع معاهده است.

**مأموریت‌ها، ذخیره، بازپخش و ابزارها**
- اهداف مأموریت پویا و مشروط به وابستگی (در انتظار ← فعال ← تکمیل‌شده/
  ناموفق/در حال بازیابی/موفقیت جایگزین) که بر اساس وضعیت جهان تعیین می‌شوند،
  نه یک اسکریپت ثابت.
- ساختار داده گراف دیالوگ شاخه‌ای برای فرماندهان، دانشمندان، مهندسان،
  دیپلمات‌ها و فرماندهان.
- ساعت کمپین قطعی (توقف/۱x/۲x/۵x/۱۰x/۲۵x) تا بازپخش‌های ضبط‌شده و
  تست‌های خودکار سناریو دقیقاً تکرارپذیر باشند.
- سیستم ذخیره چندشیاره نسخه‌بندی‌شده با اعتبارسنجی یکپارچگی بر اساس
  Checksum و ذخیره خودکار، آماده برای بازیابی پس از خرابی.
- ابزار اعتبارسنجی محتوا (شناسه‌های تکراری، ترجمه ناقص، و زیرساخت برای
  بررسی سناریو/مسیر/دیالوگ خراب) که قرار است پیش از هر بسته‌بندی در CI اجرا
  شود.

**رابط کاربری، تم‌ها و دسترس‌پذیری**
- شش تم رابط کاربری قابل تعویض در حین اجرا: **پیش‌فرض الهام‌گرفته از ویندوز
  ۱۱، Dark Navy، Light، Ocean Blue/Cyan، Red Alert، High Contrast.**
- بومی‌سازی کامل انگلیسی/فارسی/چینی با **جهت راست‌به‌چپ خودکار برای فارسی**
  و چپ‌به‌راست برای انگلیسی/چینی، بازگشت به رشته پیش‌فرض (ترجمه ناقص ←
  انگلیسی ← کلید خام، هرگز خالی نمی‌ماند)، و قابلیت‌های دسترس‌پذیری شامل
  مقیاس فونت، حالت کوررنگی و کاهش حرکت.

## پشته فناوری

| لایه | فناوری |
|---|---|
| موتور بازی | Unreal Engine 5 (نسخه‌های ۵.۳ / ۵.۴ / ۵.۵) |
| شبیه‌سازی هسته | ++C |
| چیدمان مرحله/رابط کاربری/جلوه‌های ویژه | Blueprint (در ادیتور) |
| فریم‌ورک رابط کاربری | UMG / CommonUI |
| داده | Data Table، جداول رشته JSON |
| ساخت | UnrealBuildTool، RunUAT، اسکریپت‌های PowerShell |

## ساختار پروژه

```
BlackOcean.uproject
Source/BlackOcean/
  Core/          Simulation/     Ocean/         Ships/
  Submarine/     AirAssets/      Crew/          Sensors/
  Navigation/    Fleet/          Command/       AI/
  Logistics/     Ports/          Shipyard/      Research/
  Economy/       Diplomacy/      Missions/      Dialogue/
  Save/          Replay/         UI/            Networking/
  Tools/
Content/         Maps, Ocean, Ships, Vehicles, AI, Data, UI/Themes,
                 Audio, VFX, Missions, Scenarios, Localization/{en,fa,zh}
Plugins/         (رزرو شده برای پلاگین‌های آینده هر سامانه)
Tests/           نمونه تست‌های خودکار
Scripts/         setup-windows.ps1, build-development.ps1,
                 build-shipping.ps1, run-tests.ps1, package.ps1, clean.ps1
Config/          DefaultEngine.ini, DefaultGame.ini, DefaultInput.ini
Docs/            GDD.md, TechnicalDesign.md, ModdingGuide.md,
                 LocalizationGuide.md, BuildGuide.md
INSTALLATION.md
```

## پیش‌نیازها (ویندوز ۱۰/۱۱)

- **Epic Games Launcher** — از https://store.epicgames.com/download
- **Unreal Engine 5** (۵.۳/۵.۴/۵.۵) — نصب از طریق لانچر
- **Visual Studio 2022** با ورک‌لودهای **Desktop development with C++** و
  **Game development with C++** (Windows SDK به‌طور خودکار نصب می‌شود)
- **Git** — از https://git-scm.com/download/win

## نصب و ساخت پروژه

۱. تمام موارد بخش **پیش‌نیازها** را نصب کنید.
۲. PowerShell را در پوشه `Scripts/` باز کرده و اجرا کنید:
   ```powershell
   ./setup-windows.ps1
   ```
   این اسکریپت وجود Git، ویزوال استودیو با ابزارهای ++C، Windows SDK و
   Unreal Engine 5 را بررسی و هر کمبودی را گزارش می‌کند.
۳. تولید فایل‌های پروژه و ساخت نسخه Development ادیتور:
   ```powershell
   ./build-development.ps1
   ```
۴. فایل `BlackOcean.uproject` را باز کنید تا ادیتور اجرا شود.
۵. اجرای مجموعه تست‌های خودکار:
   ```powershell
   ./run-tests.ps1
   ```
۶. ساخت نسخه Shipping:
   ```powershell
   ./build-shipping.ps1
   ```
۷. بسته‌بندی نسخه قابل توزیع:
   ```powershell
   ./package.ps1
   ```
۸. پاک‌سازی فایل‌های میانی/ساخت در هر زمان:
   ```powershell
   ./clean.ps1
   ```

جزئیات کامل مرحله‌به‌مرحله (شامل رفع اشکال) در فایل `INSTALLATION.md` آمده
است.

## توضیح درباره دامنه پروژه

این مخزن یک **زیرساخت سامانه‌ای** است: سامانه‌های اصلی گیم‌پلی که در بالا
ذکر شد با منطق واقعی و کارکردی در ++C و یک ساختار پروژه حرفه‌ای پیاده‌سازی
شده‌اند و آماده توسعه هستند. ساخت یک نسخه کامل در مقیاس AAA — شامل گرافیک
سه‌بعدی کامل، صداپیشگی، صدها ساعت محتوای روایی و یک لایه چندنفره منتشرشده —
پروژه‌ای چندساله و در مقیاس استودیو است که هیچ تحویل واحدی نمی‌تواند آن را
به‌طور کامل ارائه دهد؛ ماژول Networking عمداً فقط یک رابط (interface) برای
آن توسعه آینده است، نه یک پیاده‌سازی نهایی.

---

# 中文（简体）

## 概述

**BLACK OCEAN（黑色海洋）** 让玩家指挥一支完全虚构的海军舰队，需要同时管理
海上行动、导航、侦察、舰队后勤、海事经济、港口与船坞管理、科研、外交以及
长期战略决策，所有这些都发生在一个持续演变、真实感十足的海洋世界中。游戏
中出现的所有国家、舰艇、武器、传感器、基地与组织均为完全虚构，并非基于任
何现实军事系统建模。

核心仿真系统（海洋/天气、舰队指挥、传感器、损伤、船员、后勤、经济、外交、
人工智能、存档/回放）均使用 **C++** 编写；Blueprint 仅用于关卡搭建、动画、
UI 绑定、特效以及设计师的快速迭代。

## 核心功能

**世界与海洋**
- 全球海事仿真引擎：为每个区域维护深度、水温、洋流、浪高、能见度、天气、
  交通密度、资源可用性与威胁等级，并影响移动、探测、通信与任务。
- 动态海洋/天气漂移，支持风暴生成与昼夜循环。

**舰队、舰船与船员**
- 十三种虚构舰船类别（指挥舰、护卫舰型、驱逐舰型、巡洋舰型、类航母平台、
  潜艇、轻护卫舰、巡逻艇、两栖支援舰、后勤舰、科考船、救援船、无人机母
  舰），每种都拥有独立的机动性、传感器容量、船员编制、燃料、维护、储存、
  通信与任务定位。
- 每艘船拥有十二个可独立损坏的系统（船体、发动机、动力生成、推进、传感
  器、通信、导航、飞行甲板、内部系统、冷却、货舱、任务模块），并配有损
  伤/维修/隔离循环（进水、火灾、动力/发动机故障、传感器/通信中断、机动力
  下降）。
- 船员仿真涵盖每个岗位（舰长、工程师、导航员、传感器操作员、通信官、飞行
  组、支援组）的经验、疲劳、技能、士气与工作量，并模拟军官之间的关系
  （信任、协作、竞争、忠诚），影响协同任务效率。
- 完全面向玩法、虚构设计的潜艇循环：深度、按模式变化的浮力、电池、氧气、
  船体完整性与噪音特征。

**传感器、指挥与人工智能**
- 多传感器融合（类雷达、声呐、光学摄像、类红外、被动声学、侦察无人机、
  类卫星信号、人工报告），生成带置信度的目标分类（未知/民用/友军/中立/
  可疑/敌对），若长时间未更新则置信度自动衰减——AI 只依据已实际探测到的
  信息行动。
- 舰队 → 特遣舰队 → 中队 → 编队 → 单舰的指挥层级，命令（移动、巡逻、护
  航、侦察、搜索、救援、会合、原地待命、返港、支援、补给）会根据距离与通
  信可靠性产生真实的延迟。
- 阵营级人工智能（原则、风险偏好、经济/军事优先级）与舰队级人工智能（巡
  逻/侦察/护航/搜索/撤退/补给/维修），二者均只依据已探测到的目标推理，绝
  不依赖隐藏的真实数据。

**经济、后勤与外交**
- 国家预算在海军、科研、基础设施、后勤、工业、环境与应急储备之间分配，
  并计算财政压力指数，该指数应明显制约舰队规模与战备水平。
- 补给链路负责运输燃料、备件、食品、医疗物资、弹药等效资源、零部件与维护
  物资，并对拥堵、天气风险与中断进行建模。
- 港口拥有可配置的泊位容量、维修能力、燃料储备、仓储、船坞是否具备、贸易
  量与安全等级——**并包含玩家可自行配置的营业时间**，实时显示当前状态
  （例如“营业中——3小时20分钟后关闭”或“已关闭——45分钟后开放”），支持任
  意玩家设定的时段，或全天24小时营业。
- 科技树（传感器、推进、通信、自动化、材料、储能、水下系统、侦察系统、无
  人机、舰船设计、后勤、损管），受前置条件、时间与预算约束。
- 双边外交（关系分值，以及贸易协定/港口准入/情报共享/科研合作/航行权/搜
  救协议），每种协议类型都设有相应的信任门槛。

**任务、存档、回放与工具**
- 动态、依赖驱动的任务目标（待定 → 进行中 → 已完成/失败/恢复中/替代性成
  功），由世界状态而非固定剧本驱动。
- 用于舰长、科学家、工程师、外交官与指挥官的分支对话图数据结构。
- 确定性战役时钟（暂停/1倍/2倍/5倍/10倍/25倍速），确保录制的回放与自动化
  场景测试可以精确重现。
- 带版本管理的多存档槽系统，具备校验和完整性验证与自动存档，支持崩溃恢
  复。
- 内容验证工具（重复ID检测、缺失本地化检测，并预留了损坏场景/路线/对话
  检测的扩展点），旨在每次打包前于 CI 中运行。

**界面、主题与无障碍**
- 六套可在运行时切换的界面主题：**Windows 11 风格默认主题、深海军蓝、浅
  色、海洋蓝青、红色警报、高对比度。**
- 完整的英文/波斯语/中文本地化，波斯语**自动采用从右到左的排版方向**，
  英文/中文则为从左到右，字符串表具备回退机制（缺失翻译 → 回退英文 → 回
  退到原始键名，绝不显示空白），并提供字体缩放、色盲模式与减少动效等无障
  碍功能。

## 技术栈

| 层级 | 技术 |
|---|---|
| 引擎 | Unreal Engine 5（5.3 / 5.4 / 5.5） |
| 核心仿真 | C++ |
| 关卡/界面/特效制作 | Blueprint（在编辑器中添加） |
| 界面框架 | UMG / CommonUI |
| 数据 | Data Table、JSON 字符串表 |
| 构建 | UnrealBuildTool、RunUAT、PowerShell 自动化脚本 |

## 项目结构

```
BlackOcean.uproject
Source/BlackOcean/
  Core/          Simulation/     Ocean/         Ships/
  Submarine/     AirAssets/      Crew/          Sensors/
  Navigation/    Fleet/          Command/       AI/
  Logistics/     Ports/          Shipyard/      Research/
  Economy/       Diplomacy/      Missions/      Dialogue/
  Save/          Replay/         UI/            Networking/
  Tools/
Content/         Maps, Ocean, Ships, Vehicles, AI, Data, UI/Themes,
                 Audio, VFX, Missions, Scenarios, Localization/{en,fa,zh}
Plugins/         （预留给未来各系统的独立插件）
Tests/           自动化测试示例
Scripts/         setup-windows.ps1, build-development.ps1,
                 build-shipping.ps1, run-tests.ps1, package.ps1, clean.ps1
Config/          DefaultEngine.ini, DefaultGame.ini, DefaultInput.ini
Docs/            GDD.md, TechnicalDesign.md, ModdingGuide.md,
                 LocalizationGuide.md, BuildGuide.md
INSTALLATION.md
```

## 系统要求（Windows 10/11）

- **Epic Games Launcher** — https://store.epicgames.com/download
- **Unreal Engine 5**（5.3/5.4/5.5）— 通过启动器安装
- **Visual Studio 2022**，需勾选 **Desktop development with C++** 与
  **Game development with C++** 工作负载（会自动安装 Windows SDK）
- **Git** — https://git-scm.com/download/win

## 安装与构建

1. 安装上方“系统要求”中的全部项目。
2. 在 `Scripts/` 文件夹中打开 PowerShell 并运行：
   ```powershell
   ./setup-windows.ps1
   ```
   该脚本会检查 Git、带有 C++ 工具的 Visual Studio、Windows SDK 以及
   Unreal Engine 5，并报告任何缺失项。
3. 生成项目文件并构建 Development 版编辑器：
   ```powershell
   ./build-development.ps1
   ```
4. 双击打开 `BlackOcean.uproject` 以启动编辑器。
5. 运行自动化测试套件：
   ```powershell
   ./run-tests.ps1
   ```
6. 构建 Shipping（发行）配置：
   ```powershell
   ./build-shipping.ps1
   ```
7. 打包可分发的版本：
   ```powershell
   ./package.ps1
   ```
8. 随时清理中间/构建文件：
   ```powershell
   ./clean.ps1
   ```

完整的分步说明（含故障排查）请见 `INSTALLATION.md`。

## 项目范围说明

本仓库是一个**系统基础架构**：上述核心玩法系统均以真实、可运行的 C++ 逻
辑实现，并配有专业的项目结构，可在此基础上继续扩展。而一款完整的 3A 级
发行版——包括完整的美术资源、配音、数百小时的剧情内容以及已上线的多人联
机层——是需要工作室级团队投入数年才能完成的工程，任何单次交付都无法将其
完整实现；Networking 模块因此被有意设计为仅供未来扩展的接口层，而非最终
实现。
