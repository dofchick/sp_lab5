#include <iostream>
#include <fstream>
#include <pthread.h>
#include <string>
#include <mutex>
using namespace std;
ofstream out;
fstream fin;
pthread_mutex_t m;

int mtr[3][3] = {
    {2,4,0},
    {-2,1,3},
    {-1,0,1}
};

int vkt[3] = {1,2,-1};

int otv[3];

int och = 0;

void *vek_potok(void *arg) {
    int c = 0, sum = 0;
    int num = (long)arg;
    for (int i = 0; i < 3; i++){
        c = vkt[i] * mtr[num][i];
        sum = sum + c;
    }
    while (och < num){}
    pthread_mutex_lock(&m);
        och++;
        out.open("buff", ios::app);
        out << sum << endl;
        out.close();
    pthread_mutex_unlock(&m);
    pthread_exit(NULL);
}

int main(){
    out.open("buff");
    out << "";
    out.close();
    pthread_mutex_init(&m,NULL);
    pthread_t threads[3];
    int num[3];
    for (int i = 0; i < 3; i++ ) {
        num[i] = i;
        pthread_create(&threads[i], NULL, vek_potok, (void *)num[i]);
    }
    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);
    pthread_join(threads[2],NULL);
    fin.open("buff", ios::in);
    for (int i = 0; i < 3; i++ ){
        string b;
        getline(fin, b);
        cout << b << endl;
    }
}

