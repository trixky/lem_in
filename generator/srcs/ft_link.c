#include "ft_generator.h"

static t_bool		ft_is_in_list(int start_id, int room, t_link **list)
{
	t_link *tmp;

	tmp = list[start_id];
	while (tmp)
	{
		if (tmp->room_id == room)
			return (true);
		tmp = tmp->next;
	}
	tmp = list[room];
	while (tmp)
	{
		if (tmp->room_id == start_id)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

static t_link		*ft_choice_link(int start_id,
						t_link **list,
						int room,
						t_params params)
{
	t_link *new;

	if (!ft_is_in_list(start_id, room, list) &&
	room != start_id && room != 0 && (room != params.nb_rooms - 1))
	{
		if (!(new = ft_create_link(room)))
			return (NULL);
		new->next = list[start_id];
		new->nb = list[start_id] ? list[start_id]->nb + 1 : 1;
		list[start_id] = new;
		return (new);
	}
	if (room == params.nb_rooms - 1)
	{
		if (params.indic)
			return (NULL);
		params.indic = 1;
		return (ft_choice_link(start_id, list, 0, params));
	}
	else
		return (ft_choice_link(start_id, list, room + 1, params));
}

static void			ft_output_link(int room1, int room2)
{
	ft_putnbr(room1);
	ft_putstr("-");
	ft_putnbr(room2);
	ft_putstr("\n");
}

static void			ft_links(int room_id,
							int nb_tubes,
							t_link **list,
							t_params params)
{
	int		i;
	int		room;
	t_link	*tmp;

	i = 0;
	while (i++ < nb_tubes)
	{
		params.indic = 0;
		room = ft_randnumb(params.nb_rooms);
		if (!(tmp = ft_choice_link(room_id, list, room, params)))
			return ;
		ft_putnbr(room_id);
		ft_putstr("-");
		ft_putnbr(tmp->room_id);
		ft_putstr("\n");
	}
}

/*
** printf("-------- Room %d Nb of link %d \n", room_id, list[room_id]->nb);
*/

void				ft_print_links(t_params params)
{
	int		i;
	int		randnumb;
	t_link	**list;

	if (params.nb_rooms == 2)
	{
		ft_output_link(0, 1);
		return ;
	}
	list = ft_init_list(params.nb_rooms);
	ft_links(0, params.begin_tubes, list, params);
	i = 1;
	while ((i < params.nb_rooms - 1) && params.nb_rooms > 3)
	{
		randnumb = ft_randnumb(params.max_tubes);
		ft_links(i++, randnumb ? randnumb : 1, list, params);
	}
	ft_links(params.nb_rooms - 1, params.exit_tubes, list, params);
	ft_free_list(list, params.nb_rooms);
}
