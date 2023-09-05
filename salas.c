#include "salas.h"

loadSalas(Sala *sala[]){
    (*sala[0])->height = 10; // em quadrados
    (*sala[0])->width = 12; // em quadrados
    (*sala[0])->qtdMoveis = 0;
    (*sala[0])->movel = NULL;
    (*sala[0])->qtdSaidas = 0;
    (*sala[0])->saida = NULL;
    (*sala[0])->frame = (Vector2){(WIDTH/2) - ((*sala[0])->width)*square/2, (HEIGHT/2) - ((*sala[0])->height)*square/2};

    (*sala[0])->hitbox = (Rectangle){(WIDTH/2) - ((*sala[0])->width - 2)*square/2, (HEIGHT/2) - ((*sala[0])->height - 2)*square/2,
                                  (WIDTH/2) + ((*sala[0])->width - 2)*square/2, (HEIGHT/2) + ((*sala[0])->height - 2)*square/2};
}