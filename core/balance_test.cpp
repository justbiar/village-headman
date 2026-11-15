// Bot vs bot balance runner: plays many seeded games and prints how they end.
// Build: clang++ -std=c++17 -O2 VHSim.cpp balance_test.cpp -o balance && ./balance [games]
#include "VHSim.h"

#include <cstdio>
#include <cstdlib>
#include <map>

using namespace vh;

static const char* kProfile[3] = {"Çiftçi", "Militarist", "Dindar"};

int main(int argc, char** argv) {
    const int games = argc > 1 ? std::atoi(argv[1]) : 300;
    const int maxTurns = 80;

    // One verbose game so the turn log can be read.
    {
        Game g(7);
        for (int t = 0; t < 12 && !g.Over(); ++t) {
            g.Resolve(g.BotOrders(0, 0), g.BotOrders(1, 1));
            std::printf("-- Tur %d --\n", g.Turn() - 1);
            for (const LogLine& l : g.LastLog()) std::printf("  [%s] %s\n", g.Side(l.side).name.c_str(), l.text.c_str());
            for (int s = 0; s < 2; ++s) {
                const Village& v = g.Side(s);
                std::printf("  %s: altın %.0f gıda %.0f EP %.0f nüfus %.1f asker %d psk %.0f ordu %.0f tarikat %.0f can %.0f\n",
                            v.name.c_str(), v.gold, v.food, v.ep, v.Population(), v.soldiers, v.psych, v.armyPower, v.cult, v.hallHp);
            }
        }
    }

    std::printf("\n== %d oyun, her eşleşme ==\n", games);
    for (int p0 = 0; p0 < 3; ++p0)
        for (int p1 = 0; p1 < 3; ++p1) {
            int wins[3] = {0, 0, 0};
            long turnsSum = 0;
            std::map<int, int> endings;
            for (int i = 0; i < games; ++i) {
                Game g(1000 + i * 7919);
                while (!g.Over() && g.Turn() <= maxTurns) g.Resolve(g.BotOrders(0, p0), g.BotOrders(1, p1));
                turnsSum += g.Turn() - 1;
                int w = g.Winner();
                wins[w == -1 ? 2 : w]++;
                for (int s = 0; s < 2; ++s) if (g.Side(s).ending != Ending::None) endings[(int)g.Side(s).ending]++;
            }
            std::printf("%-10s vs %-10s  A %3d%%  B %3d%%  berabere/süre %3d%%  ort. tur %4.1f  |", kProfile[p0], kProfile[p1],
                        wins[0] * 100 / games, wins[1] * 100 / games, wins[2] * 100 / games, (double)turnsSum / games);
            for (auto& e : endings) std::printf(" %s:%d", EndingName((Ending)e.first), e.second);
            std::printf("\n");
        }
    return 0;
}
