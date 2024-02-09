#include <stdio.h>
#include "time.h"
#include <string.h>
#define lmax 99

struct computer{

    struct dimensions{
        int weight;
        struct size{
            int width;
            int length;
            int high;
        }size;
    }dimensions;

    int volume;

    struct processor{
        char name[lmax];
        int frequency;
    }processor;

    int price;

    struct manufacturer{
        char manufacturerName[lmax];
        int year;
    }manufacturer;
};

int check_time(int year_pr) {
    int m = 0;
    time_t t;
    struct tm *aTm = localtime(&t);
    int te = aTm -> tm_year + 1900;
    if (te >= year_pr && year_pr >= 1886)
        m = 1; return m;
}

int input_computer(struct computer *computer){

    int num_of_computer;

    FILE *file = fopen("/Users/liz0khse/CLionProjects/dop6/dop_in.txt", "r");

    if (file == NULL){
        printf("open error\n");
        return 1;
    }

    fscanf(file, "%d", &num_of_computer);

    for(struct computer *curr = computer; curr < num_of_computer + computer; curr++){

        while(fscanf(file, "%d", &curr -> dimensions.weight)!=1 || curr -> dimensions.weight<=0){
            int checker;
            while((checker=getchar())!="\n" && checker!=EOF){
                printf("enter right, fool! check your file\n");
            }
        }
        while(fscanf(file, "%d", &curr -> dimensions.size.width)!=1 || curr -> dimensions.size.width <= 0){
            int checker;
            while((checker=getchar())!="\n" && checker!=EOF){
                printf("enter right, fool! check your file\n");
            }
        }
        while(fscanf(file, "%d", &curr -> dimensions.size.length)!=1 || curr -> dimensions.size.length <= 0){
            int checker;
            while((checker=getchar())!="\n" && checker!=EOF){
                printf("enter right, fool! check your file\n");
            }
        }
        while(fscanf(file, "%d", &curr -> dimensions.size.high)!=1 || curr -> dimensions.size.high <= 0){
            int checker;
            while((checker=getchar())!="\n" && checker!=EOF){
                printf("enter right, fool! check your file\n");
            }
        }
        while(fscanf(file, "%d", &curr -> volume)!=1 || curr -> volume<=0){
            int checker;
            while((checker=getchar())!="\n" && checker!=EOF){
                printf("enter right, fool! check your file\n");
            }
        }

        fscanf(file, "%s", curr -> processor.name);

        while(fscanf(file, "%d", &curr -> processor.frequency)!=1 || curr -> processor.frequency<=0){
            int checker;
            while((checker=getchar())!="\n" && checker!=EOF){
                printf("enter right, fool! check your file\n");
            }
        }
        while(fscanf(file, "%d", &curr -> price)!=1 || curr -> price<=0){
            int checker;
            while((checker=getchar())!="\n" && checker!=EOF){
                printf("enter right, fool! check your file\n");
            }
        }

        fscanf(file, "%s", curr -> manufacturer.manufacturerName);
        while(fscanf(file, "%d", &curr -> manufacturer.year)!=1 || curr -> manufacturer.year<=0 || (check_time(curr -> manufacturer.year)==0)){
            int checker;
            while((checker=getchar())!="\n" && checker!=EOF){
                printf("enter right, fool! check your file\n");
            }
        }

    }

    fclose(file);

    return num_of_computer;
}

void check_market(int *num_of_computer, struct computer *computer){

    printf("your number of computers: %d \n", *num_of_computer);
    puts("");

    puts("market:\n");
    for(struct computer *curr = computer; curr < *num_of_computer + computer; curr++){
        printf("          furniture #%d\n", curr-computer+1);

        printf("weght..................%d\n", curr -> dimensions.weight);
        printf("width..................%d\n", curr -> dimensions.size.width);
        printf("lenght.................%d\n", curr -> dimensions.size.length);
        printf("high...................%d\n", curr -> dimensions.size.high);
        printf("volume.................%d\n", curr -> volume);
        printf("processor name.........%s\n", curr -> processor.name);
        printf("processor frequency....%d\n", curr -> processor.frequency);
        printf("price..................%d\n", curr -> price);
        printf("manufacturer name......%s\n", curr -> manufacturer.manufacturerName);
        printf("manufacturer year......%d\n", curr -> manufacturer.year);
        puts("");
    }
}

void add_to_cart(struct computer item, struct computer cart[], int *cart_count) {
    if (*cart_count < lmax) {
        cart[*cart_count] = item;
        (*cart_count)++;
        printf("Товар успешно добавлен в корзину.\n");
    } else {
        printf("Ошибка: корзина полная.\n");
    }
}
void display_cart(struct computer cart[], int cart_count) {
    if (cart_count == 0) {
        printf("Корзина пуста.\n");
    } else {
        printf("Содержимое корзины:\n");
        for (int i = 0; i < cart_count; i++) {
            printf("%d. Название: %s, Цена: %d\n",
                   i + 1, cart[i].processor.name, cart[i].price);
        }
    }
}

int calculate_total(struct computer cart[], int cart_count) {
    int total = 0;
    for (int i = 0; i < cart_count; i++) {
        total += cart[i].price;
    }
    return total;
}

int main(){
    struct computer cart[lmax];
    struct computer computer[lmax];
    int num_of_computer, shoplist[lmax], k, l=500;
    int cart_count = 0, selected_item, total, discount;
    char choice;

    num_of_computer = input_computer(computer);

    if(num_of_computer == 0){
        puts("check your file");
    }
    else{
        check_market(&num_of_computer, computer);

        do {
            printf("Доступные товары:\n");
            for (int i = 0; i < num_of_computer; i++) {
                printf("%d. %s\n", i + 1, computer[i].processor.name);
            }
            printf("%d. Показать корзину\n", num_of_computer + 1);

            printf("Выберите товар для добавления в корзину или показа корзины: ");
            scanf("%d", &selected_item);

            if (selected_item >= 1 && selected_item <= num_of_computer) {
                add_to_cart(computer[selected_item - 1], cart, &cart_count);
            } else if (selected_item == num_of_computer + 1) {

                display_cart(cart, cart_count);

                total = calculate_total(cart, cart_count);
                printf("Общая сумма корзины: %d\n", total);

                printf("Введите размер скидки (в процентах): ");
                scanf("%d", &discount);

                total -= total * discount / 100;
                printf("Сумма к оплате после применения скидки: %d\n", total);
            } else {
                printf("Ошибка: некорректный выбор товара.\n");
            }

            printf("Хотите продолжить добавление товаров в корзину или показать корзину? (y/n): ");
            scanf(" %c", &choice);

        } while (choice == 'y' || choice == 'Y');
    }
}