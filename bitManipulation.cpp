int numberOfBits (int state) {
    int cnt = 0;
    while(state) {
        state &= (state - 1);
        cnt++;
    }
    return cnt;
}

bool hasIthBit(int state, int i) {
    return state & (1 << i);
}

int addBit(int state, int i) {
    return state | (1 << i);
}
// will be improved