/*My File Handler*/

int fd;
		unsigned long f = 0;
		unsigned long a = ms->var[0];
		unsigned long b = ms->var[1];
		unsigned long c = ms->var[2];
		unsigned long d = ms->var[3];
		int g = 0;
		unsigned char *msg;
		int new_len;

		new_len = 0;
		if ((fd = open(args[i], O_RDONLY)) > -1)
		{
			printf("file \'%s\': is valid\n", args[i]);
			read_in_file(fd, ms, args[i]);
			// md5_update((uint8_t*)args[i], init_len);
			pre_processing(ms);
			// printf("a = %#010x\t b = %#010x\t c = %#010x\t d = %#010x\n", ms->var[0], ms->var[1], ms->var[2], ms->var[3]);
			
			new_len = ms->total_bytes + 1;
			while (new_len % 64 != 56)
				new_len++;
			msg = (unsigned char*)malloc(sizeof(new_len + 64));
			ft_bzero(msg, new_len + 64);
			ft_strcpy((char*)msg, args[i]);
			printf("msg = %s\n", msg);
			int i = -1;

			while (++i < 64)
			{
				if (i < 16)
				{
					f = F(ms->var[1], ms->var[2], ms->var[3]);
					g = i;
				}
				else if(i < 32)
				{
					f = G(ms->var[1], ms->var[2], ms->var[3]);
					g = (i * 5) % 16;
				}
				else if (i < 48)
				{
					f = H(ms->var[1], ms->var[2], ms->var[3]);
					g = (i * 3) % 16;
				}
				else
				{
					f = I(ms->var[1], ms->var[2], ms->var[3]);
					g = (i * 5) % 16;
				}
				f = f + a + k[i] + ms->buf[g];
				a = d;
				d = c;
				c = b;
				b = b + ROTATE_LEFT(f, s[i]);
			}
			ms->var[0] += a;
			ms->var[1] += b;
			ms->var[2] += c;
			ms->var[3] += d;
		}
		printf("a: %x\n", (int)a);
		printf("b: %x\n", (int)b);
		printf("c: %x\n", (int)c);
		printf("d: %x\n", (int)d);
		close(fd);