#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

void clean_ressources(SDL_Window* w,SDL_Renderer* r,SDL_Texture* t);

void end_program(char* c, SDL_Window* w,SDL_Renderer* r,SDL_Texture* t){
		SDL_Log("CREATION %s ECHOUEE > %s",c ,SDL_GetError());
		clean_ressources(w,r,t);
		SDL_Quit();
		exit(EXIT_FAILURE);
}


void clean_ressources(SDL_Window* w,SDL_Renderer* r,SDL_Texture* t){
	if(t!=NULL){
		SDL_DestroyTexture(t);
	}
	if(r!=NULL){
		SDL_DestroyRenderer(r);
	}
	if(w!=NULL){
		SDL_DestroyWindow(w);
	}
}


int draw_pixel(SDL_Renderer* renderer,int x,int y,Uint8 r,Uint8 g,Uint8 b){
	if(SDL_SetRenderDrawColor(renderer,r,g,b,255) != EXIT_SUCCESS){
		return EXIT_FAILURE;
	}
	SDL_Rect pixel = {x,y,1,1};
	if(SDL_RenderFillRect(renderer,&pixel) != EXIT_SUCCESS){
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int fill_window(SDL_Renderer* renderer,Uint8 r,Uint8 g,Uint8 b){
	if(SDL_SetRenderDrawColor(renderer,r,g,b,255) != EXIT_SUCCESS){
		return EXIT_FAILURE;
	}

	if(SDL_RenderFillRect(renderer,NULL) != EXIT_SUCCESS){
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


Uint8 modulo(int a,int b){
	while(a>=b){
		a = a-b;
	}
	return (Uint8) a;
}

Uint8 convert_hex_to_int(char hex){
	int r = -1;
	char n = hex;
	if(n == 'a'){
		r=10;
	}
	if(n=='b'){
		r = 11;
	}
	if(n=='c'){
		r = 12;
	}
	if(n == 'd'){
		r=13;
	}
	if(n=='e'){
		r = 14;
	}
	if(n=='f'){
		r = 15;
	}
	if(r==-1){
		r = n - '0';
	}
	return modulo(r, 16);
}


Uint8* convert_hex_to_int_color(char* hex){
	Uint8* T = malloc(sizeof(Uint8)*3);
	Uint8 seize = 16;
	for(Uint8 i =0;i<3;i+=1){
		T[i] = (Uint8) (convert_hex_to_int(hex[2*i])*seize + convert_hex_to_int(hex[2*i+1]));
	}
	return T;
}



int CINI_draw_pixel(SDL_Renderer* renderer,int x,int y,char* c){
	Uint8* T = convert_hex_to_int_color(c);
	if(draw_pixel(renderer,x,y,T[0],T[1],T[2]) != EXIT_SUCCESS){
		free(T);
		return EXIT_FAILURE;
	}
	free(T);
	return EXIT_SUCCESS;
}


int CINI_fill_window(SDL_Renderer* renderer,char* c){
	Uint8* T = convert_hex_to_int_color(c);
	if(fill_window(renderer,T[0],T[1],T[2]) != EXIT_SUCCESS){
		free(T);
		return EXIT_FAILURE;
	}
	free(T);
	return EXIT_SUCCESS;
}

void CINI_loop(SDL_Renderer* renderer){
	SDL_RenderPresent(renderer);
	SDL_bool displayed = SDL_TRUE;
	while(displayed){
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_KEYUP:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							displayed = SDL_FALSE;
							break;
						default:
							break;
					}
					break;
				case SDL_QUIT:
					displayed = SDL_FALSE;
					break;
				default:
					break;
			}
		}
	}

}

int main(int argc, char **argv){
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;
	//set window size here
	int TAILLE_FENETRE_W = 1000;
	int TAILLE_FENETRE_H = 500;

	if(SDL_Init(SDL_INIT_VIDEO) != EXIT_SUCCESS)
	{
		end_program("INIT",NULL,NULL,NULL);
	}	
	
	//Execution programme
	window = SDL_CreateWindow("HéhéhéhA loul",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,TAILLE_FENETRE_W,TAILLE_FENETRE_H,0);
	
	if(window == NULL)
	{
		end_program("FENETRE",NULL,NULL,NULL);
	}
	
	
	renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_SOFTWARE);
	
	if(renderer == NULL){
		end_program("renderer",window,NULL,NULL);	
	}
	//Write your code here
	
	
	
	end_program("PAS DECHEC",window,renderer,texture);
	SDL_Quit();
	return 0;
}
