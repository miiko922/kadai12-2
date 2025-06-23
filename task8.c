#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct place{                   //場所についての構造体
    double X;                      //X座標
    double Y;                      //Y座標
};
struct time{                    //時間についての構造体
    int hour;
    int minute;
};
struct shop {
    char name[64];                //名前
    struct place shop_place;            //場所
    int genre;                          //ジャンル
    //1:和食
    //2:洋食
    //3:中華
    //4:カフェ
    //5:その他
    struct time open;                   //開業時間
    struct time close;                  //終業時間
    int price;                          //価格帯
    double rep;                         //評判
    double dis;                         //現在地からの距離(初期値は0)
};
double distance(struct place shop, struct place now)                 //距離を計算する関数
{
    double dis;
    dis = pow((shop.X - now.X) * (shop.X - now.X) + (shop.Y - now.Y) * (shop.Y - now.Y), 0.5);
    return dis;
}
//可変長配列を実装
struct DynamicArray{
    struct shop *data;
    size_t size;
    size_t capacity;
};
// 動的配列の初期化
void initArray(struct DynamicArray *a, size_t initialCapacity) {
    a->data = (struct shop *)malloc(initialCapacity * sizeof(struct shop));
    a->size = 0;
    a->capacity = initialCapacity;
}
// 動的配列に要素を追加
void insertArray(struct DynamicArray *a, struct shop element) {
    if (a->size == a->capacity) {
        a->capacity *= 2;
        a->data = (struct shop *)realloc(a->data, a->capacity * sizeof(struct shop));
    }
    a->data[a->size++] = element;
}
// 動的配列の解放
void freeArray(struct DynamicArray *a) {
    free(a->data);
    a->data = NULL;
    a->size = a->capacity = 0;
}
//距離順にソートする
void sortArrayDis(struct DynamicArray *a) {
    for (size_t i = 0; i < a->size - 1; i++) {
        for (size_t j = a->size - 1; j > i; j--) {
            if (a->data[j - 1].dis > a->data[j].dis) {
                struct shop tmp = a->data[j];
                a->data[j] = a->data[j - 1];
                a->data[j - 1] = tmp;
            }
        }
    }
}
//価格順
void sortArrayPrice(struct DynamicArray *a) {
    for (size_t i = 0; i < a->size - 1; i++) {
        for (size_t j = a->size - 1; j > i; j--) {
            if (a->data[j - 1].price > a->data[j].price) {
                struct shop tmp = a->data[j];
                a->data[j] = a->data[j - 1];
                a->data[j - 1] = tmp;
            }
        }
    }
}
//評価順
void sortArrayRep(struct DynamicArray *a) {
    for (size_t i = 0; i < a->size - 1; i++) {
        for (size_t j = a->size - 1; j > i; j--) {
            if (a->data[j - 1].rep < a->data[j].rep) {
                struct shop tmp = a->data[j];
                a->data[j] = a->data[j - 1];
                a->data[j - 1] = tmp;
            }
        }
    }
}
int main(void)
{
    //ファイルを読み込みshopsに追加する
    struct DynamicArray shops;
    initArray(&shops, 1);
    //店を追加するor店を検索する
    int select;
    puts("1:店を追加する");
    puts("2:店を検索する");
    scanf("%d", &select);
    if (select == 1){
        ////店を追加する
        int error = 1;
        //////店情報を入力する
        char name[64];                //名前
        double shop_place_x;
        double shop_place_y;
        int genre;                          //ジャンル
        int open_hour;
        int open_minute;
        int close_hour;
        int close_minute;
        int price;                          //価格帯
        double rep;                         //評判
        double dis;                         //現在地からの距離(初期値は0)
        while(error == 1){
            error = 0;
            printf("店名：");
            scanf("%s", name);
            printf("店の位置(緯度)：");
            scanf("%lf", &shop_place_x);
            printf("店の位置(経度)：");
            scanf("%lf", &shop_place_y);
            printf("店のジャンル：");
            scanf("%d", &genre);
            if(genre < 1 || genre > 5){
                error = 1;
            }
            printf("開店時間(時間)：");
            scanf("%d", &open_hour);
            if(open_hour < 0 || open_hour > 24){
                error = 1;
            }
            printf("開店時間(分)：");
            scanf("%d", &open_minute);
            if(open_minute < 0 || open_minute > 59){
                error = 1;
            }
            printf("閉店時間(時間)：");
            scanf("%d", &close_hour);
            if(close_hour < 0 || close_hour > 24){
                error = 1;
            }
            printf("閉店時間(分)：");
            scanf("%d", &close_minute);
            if(close_minute < 0 || close_minute > 59){
                error = 1;
            }
            printf("価格帯(1000円単位)：");
            scanf("%d", &price);
            if(price < 0 || price % 1000 != 0){
                error = 1;
            }
            printf("評判：");
            scanf("%lf", &rep);
            if(rep < 0 || rep > 5){
                error = 1;
            }
            if(error == 0){
                int select2;
                puts("以下の情報で間違いありませんか？");
                printf("---%s----------\n", name);
                printf("店の位置：(%f, %f)\n", shop_place_x, shop_place_y);
                if (genre == 1){
                    printf("店のジャンル：和食\n");
                }
                if (genre == 2){
                    printf("店のジャンル：洋食\n");
                }
                if (genre == 3){
                    printf("店のジャンル：中華\n");
                }
                if (genre == 4){
                    printf("店のジャンル：カフェ\n");
                }
                if (genre == 5){
                    printf("店のジャンル：その他\n");
                }
                printf("開店時間：%d:%02d\n", open_hour, open_minute);
                printf("閉店時間：%d:%02d\n", close_hour, close_minute);
                printf("価格帯：約%d円\n", price);
                printf("評価：%.1f\n", rep);
                puts("----------------");
                printf("1:Yes / 2:No\n");
                scanf("%d", &select2);
                if (select2 == 1){
                    //////shopinfoに書き込む
                    FILE *fp;

                    if ((fp = fopen("shopinfo.txt", "a")) == NULL){
                        printf("\aファイルをオープンできません。\n");
                    }else{
                        fprintf(fp, "%s %lf %lf %d %d %d %d %d %d %lf\n", name, shop_place_x, 
                            shop_place_y, genre, open_hour, open_minute, close_hour, 
                            close_minute, price, rep);
                    }
                }
                if (select2 != 1){
                    printf("入力しなおしてください。\n");
                }            
            }
            if(error == 1){
                printf("入力内容に間違いがあります。入力しなおしてください。\n");
            }
        }                
    }
    if (select == 2){
        ////店を検索する
        //ファイルを読み込みshopsに追加する
        FILE *fp;
        if ((fp = fopen("shopinfo.txt", "r")) == NULL){
            printf("\aファイルをオープンできません。\n");
        }else{
            char name[64];                //名前
            double shop_place_x;
            double shop_place_y;
            int genre;                          //ジャンル
            int open_hour;
            int open_minute;
            int close_hour;
            int close_minute;
            int price;                          //座席数
            double rep;                         //評判
            double dis;                         //現在地からの距離(初期値は0)
            while (fscanf(fp, "%s%lf%lf%d%d%d%d%d%d%lf", name, &shop_place_x, 
                &shop_place_y, &genre, &open_hour, &open_minute, &close_hour,
                 &close_minute, &price, &rep) == 10){
                struct shop Shop;
                strcpy(Shop.name, name);
                Shop.shop_place = (struct place){shop_place_x, shop_place_y};
                Shop.genre = genre;
                Shop.open = (struct time){open_hour, open_minute};
                Shop.close = (struct time){close_hour, close_minute};
                Shop.price = price;
                Shop.rep = rep;
                Shop.dis = 0;
                insertArray(&shops, Shop);                       
            }
            fclose(fp);
        }
        //////絞り込み条件を入力する
        int select3;
        int select4;
        double now_p_x;
        double now_p_y;
        printf("出発地の緯度は：");
        scanf("%lf", &now_p_x);
        printf("出発地の経度は：");
        scanf("%lf", &now_p_y);
        struct place now_p = {now_p_x,now_p_y};
        int error2 = 1;
        puts("検索する飲食店のジャンルを指定してください。");
        while(error2 == 1){
            error2 = 0;
            puts("1:和食\n2:洋食\n3:中華\n4:カフェ\n5:その他");
            scanf("%d", &select3);
            if(select3 < 1 || select3 > 5){
                error2 = 1;
                printf("1~5の整数で指定してください。\n");
            }
        }
        int error3 = 1;
        puts("ソート順を選択してください");
        while(error3 == 1){
            error3 = 0;
            puts("1:近い順\n2:価格順(半径1.0以内)\n3:評価順(半径1.0以内)");
            scanf("%d", &select4);
            if(select4 < 1 || select4 > 3){
                error3 = 1;
                printf("1~3の整数で指定してください。\n");
            }
        }
        time_t currentTime;
        time(&currentTime);
        struct tm *local = localtime(&currentTime);
        //////距離を計算する
        for (size_t i = 0; i < shops.size; i++) {
            shops.data[i].dis = distance(shops.data[i].shop_place, now_p);
        }
        //////距離順にソートする
        sortArrayDis(&shops);
        if(select4 == 1){
            printf("条件に一致する店を(%f, %f)から近い順に表示します。\n", now_p_x, now_p_y);
            for (size_t i = 0; i < shops.size; i++){
                if(shops.data[i].genre == select3){
                    printf("---%s", shops.data[i].name);
                    if((local->tm_hour > shops.data[i].open.hour ||
                        (local->tm_hour == shops.data[i].open.hour && local->tm_min >
                             shops.data[i].open.minute))&&(local->tm_hour < shops.data[i].close.hour 
                                || (local->tm_hour == shops.data[i].close.hour && local->tm_min <
                                     shops.data[i].close.minute))){
                        printf("(営業中)");
                    }else{
                        printf("(営業していません)");
                    }
                    printf("----------\n");
                    printf("店の位置：(%f, %f)\n", shops.data[i].shop_place.X, shops.data[i].shop_place.Y);
                    printf("店までの距離：%f\n", shops.data[i].dis);
                    if (shops.data[i].genre == 1){
                        printf("店のジャンル：和食\n");
                    }
                    if (shops.data[i].genre == 2){
                        printf("店のジャンル：洋食\n");
                    }
                    if (shops.data[i].genre == 3){
                        printf("店のジャンル：中華\n");
                    }
                    if (shops.data[i].genre == 4){
                        printf("店のジャンル：カフェ\n");
                    }
                    if (shops.data[i].genre == 5){
                        printf("店のジャンル：その他\n");
                    }
                    printf("開店時間：%d:%02d\n", shops.data[i].open.hour, shops.data[i].open.minute);
                    printf("閉店時間：%d:%02d\n", shops.data[i].close.hour, shops.data[i].close.minute);
                    printf("価格帯：約%d円\n", shops.data[i].price);
                    printf("評価：%.1f\n", shops.data[i].rep);
                    puts("----------------");
                }
            }
        }
        if(select4 == 2){
            printf("条件に一致する店を価格帯が低い順に表示します。\n");
            sortArrayPrice(&shops);
            for (size_t i = 0; i < shops.size; i++){
                if(shops.data[i].genre == select3 && shops.data[i].dis <= 1.0){
                    printf("---%s", shops.data[i].name);
                    if((local->tm_hour > shops.data[i].open.hour || (local->tm_hour == 
                        shops.data[i].open.hour && local->tm_min > shops.data[i].open.minute))
                        &&(local->tm_hour < shops.data[i].close.hour || (local->tm_hour == shops.data[i].close.hour
                             && local->tm_min < shops.data[i].close.minute))){
                        printf("(営業中)");
                    }else{
                        printf("(営業していません)");
                    }
                    printf("----------\n");
                    printf("店の位置：(%f, %f)\n", shops.data[i].shop_place.X, shops.data[i].shop_place.Y);
                    printf("店までの距離：%f\n", shops.data[i].dis);
                    if (shops.data[i].genre == 1){
                        printf("店のジャンル：和食\n");
                    }
                    if (shops.data[i].genre == 2){
                        printf("店のジャンル：洋食\n");
                    }
                    if (shops.data[i].genre == 3){
                        printf("店のジャンル：中華\n");
                    }
                    if (shops.data[i].genre == 4){
                        printf("店のジャンル：カフェ\n");
                    }
                    if (shops.data[i].genre == 5){
                        printf("店のジャンル：その他\n");
                    }
                    printf("開店時間：%d:%02d\n", shops.data[i].open.hour, shops.data[i].open.minute);
                    printf("閉店時間：%d:%02d\n", shops.data[i].close.hour, shops.data[i].close.minute);
                    printf("価格帯：%d\n", shops.data[i].price);
                    printf("評価：%.1f\n", shops.data[i].rep);
                    puts("----------------");
                }
            }
        }
        if(select4 == 3){
            printf("条件に一致する店を評価が高い順に表示します。\n");
            sortArrayRep(&shops);
            for (size_t i = 0; i < shops.size; i++){
                if(shops.data[i].genre == select3 && shops.data[i].dis <= 1.0){
                    printf("---%s", shops.data[i].name);
                    if((local->tm_hour > shops.data[i].open.hour || (local->tm_hour == shops.data[i].open.hour &&
                         local->tm_min > shops.data[i].open.minute))&&(local->tm_hour < shops.data[i].close.hour ||
                             (local->tm_hour == shops.data[i].close.hour && local->tm_min < shops.data[i].close.minute))){
                        printf("(営業中)");
                    }else{
                        printf("(営業していません)");
                    }                    
                    printf("----------\n");
                    printf("店の位置：(%f, %f)\n", shops.data[i].shop_place.X, shops.data[i].shop_place.Y);
                    printf("店までの距離：%f\n", shops.data[i].dis);
                    if (shops.data[i].genre == 1){
                        printf("店のジャンル：和食\n");
                    }
                    if (shops.data[i].genre == 2){
                        printf("店のジャンル：洋食\n");
                    }
                    if (shops.data[i].genre == 3){
                        printf("店のジャンル：中華\n");
                    }
                    if (shops.data[i].genre == 4){
                        printf("店のジャンル：カフェ\n");
                    }
                    if (shops.data[i].genre == 5){
                        printf("店のジャンル：その他\n");
                    }
                    printf("開店時間：%d:%02d\n", shops.data[i].open.hour, shops.data[i].open.minute);
                    printf("閉店時間：%d:%02d\n", shops.data[i].close.hour, shops.data[i].close.minute);
                    printf("価格帯：約%d円\n", shops.data[i].price);
                    printf("評価：%.1f\n", shops.data[i].rep);
                    puts("----------------");
                }
            }
        }    
        // メモリ解放
        freeArray(&shops);
    }    
    return 0;

}//finish
//今後処理を追加
