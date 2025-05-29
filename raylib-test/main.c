#include <stdio.h>
#include <raylib.h>
#include <stdint.h>
#include <unistd.h>


void callback_processor(void *buffer, unsigned int frames)
{
	float *float_buffer = (float *) buffer;
	for (unsigned int i = 0; i < frames; i++) {
		printf("%f\n", float_buffer[i]);
	}
}

int main(void)
{
	InitAudioDevice();

	Music music = LoadMusicStream("reach-for-the-summit.ogg");
	printf("%s\n", (IsMusicValid(music) ? "true" : "false"));

	AttachAudioMixedProcessor(callback_processor);

	PlayMusicStream(music);
	music.looping = false;

	while(1) {
		UpdateMusicStream(music);
	}

	sleep(10);

	// while (!WindowShouldClose())
	// {
	// 	BeginDrawing();
	//
	// 	ClearBackground(RAYWHITE);
	// 	DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
	//
	// 	EndDrawing();
	// }

	CloseAudioDevice();
	return 0;
}
