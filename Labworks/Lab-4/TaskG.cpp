#include <iostream>
#include <cstdint>


struct State {
    int pos;
    int placed_mask;
};

int main() {
    int H, W;
    std::cin >> H >> W;

    if ((H * 1 * W) % 2 != 0) {
        std::cout << 0;
        return 0;
    }

    if (H < W) {
        int tmp = H;
        H = W; 
        W = tmp;
    }

    const int max_mask = 1 << W;

    uint64_t* dp = new uint64_t[max_mask];
    uint64_t* dp_next = new uint64_t[max_mask];

    for (int i = 0; i < max_mask; ++i) {
        dp[i] = 0;
    }
    dp[0] = 1;

    
    State stack[1 << 20]; 

    for (int row = 0; row < H; ++row) {
        for (int i = 0; i < (1 << W); ++i) {
            dp_next[i] = 0;
        }

        for (int mask = 0; mask < (1 << W); ++mask) {
            if (dp[mask] == 0) {
                continue;
            }

            int top = 0;
            stack[top++] = {0, 0}; 

            while (top > 0) {
                State s = stack[--top];
                int pos = s.pos;
                int placed = s.placed_mask;

                if (pos == W) {
                    dp_next[placed] += dp[mask];
                    continue;
                }

                if (mask & (1 << pos)) {
                    stack[top++] = {pos + 1, placed};
                    continue;
                }

                stack[top++] = {pos + 1, placed | (1 << pos)};

                if (pos + 1 < W && !(mask & (1 << (pos + 1)))) {
                    stack[top++] = {pos + 2, placed};
                }
            }
        }

        uint64_t* temp = dp;
        dp = dp_next;
        dp_next = temp;
    }

    std::cout << dp[0];

    delete[] dp;
    delete[] dp_next;

    return 0;
}