#include <core/deinit.h>

void		sh_data_free(t_sh_data *data)
{
    //TODO free envs
    (void)data;
    return;
}

void sh_restore_tattr(struct termios *tattr)
{
	struct termios term;

	term = *tattr;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) < 0)
    {
        //TODO: perror("stdin"); interdit de perror
	    ft_printf("ERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRRERRORRRRR");
	    return;
    }
      free(tattr);
      tattr = NULL;
    return;
}

void			sh_deinit(t_sh_data *data)
{
    sh_restore_tattr(data->tattr);
    sh_data_free(data);
}
