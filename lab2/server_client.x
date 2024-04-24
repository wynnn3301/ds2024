typedef string filename<255>;
typedef string data<500>;

program FILE_INTERACT_PROG {
    version DEMO {
        int open(filename) = 1;
        void close(int) = 2;
        data read(int) = 3;
    } = 1;
} = 1;
