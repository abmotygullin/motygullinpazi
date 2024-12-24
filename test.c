/* --------------------------------------------------------------------------------- */
/* Пример example-g03n01.c                                                           */
/* --------------------------------------------------------------------------------- */
#include <stdio.h>
#include <libakrypt.h>
#include <unistd.h>

int main(void)
{
    /* код ошибки, возвращаемый функциями библиотеки */
    int error = ak_error_ok;
    /* статус выполнения программы */
    int exitstatus = EXIT_FAILURE;
    /* контекст алгоритма блочного шифрования */
    struct bckey ctx;
    struct random rnd;
    /* константное значение ключа */
    
    ak_uint8 generated[800];
    ak_uint8 key[32] = { 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07, 0x08,0x09,0x0A,0x0B, 0x0C,0x0D,0x0E,0x0F,
                       0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17, 0x18,0x19,0x1A,0x1B, 0x1C,0x1D,0x1E,0x1F, };

    /* инициализируем библиотеку */
    if (ak_libakrypt_create(NULL) != ak_true) {
        ak_libakrypt_destroy();
        return EXIT_FAILURE;
    }

    ak_bckey_create_magma(&ctx);
    ak_bckey_set_key(&ctx, key, 32);
    ak_random_create_magma(&rnd, &ctx);
    rnd.random(&rnd, generated, 800);
    write(1, "a", 1);
    printf("%s\n\n", ak_ptr_to_hexstr(generated, 40, ak_false));
    printf("%s\n\n", ak_ptr_to_hexstr((ak_uint8*)generated + 760, 40, ak_false));
    rnd.free(&rnd);

    /* завершаем работу */
    if (error == ak_error_ok) exitstatus = EXIT_SUCCESS;
    ak_libakrypt_destroy();
    return exitstatus;
}