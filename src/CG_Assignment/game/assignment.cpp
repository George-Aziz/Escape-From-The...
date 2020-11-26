/*********************************************************************************
 * Author: George Aziz
 * Date Created: 13/10/2020
 * Date Last Modified : 22/10/2020
 * Purpose: Slender-Man like game created in openGL
 * 
 * Parts of code implementations retrieved from Computer Graphics 2020 Semester 2
 * Practical 1 - OpenGL Sample 1,2 & 2.5.3 light_casters_spot  
 * 
 * Texture References:
 * MC_Grass (Ground Grass) Retrieved From: https://www.pinterest.com.au/pin/23010648074488766/
 * Creeper Face (Edited) Retrieved From: https://www.pinterest.co.uk/pin/618752436275546136/
 * Leaves (Tree Leaves) Retrieved From: https://babybro17gaming.home.blog/minecraft-leaves/
 * Obsidian Retrieved From: https://www.pinterest.com.au/pin/286752701251910559/
 * ManFace (Did it myself on PixlArt but based off): https://static.wikia.nocookie.net/hermitcraft/images/1/12/MumboFace.png/revision/latest?cb=20140614190622
 * PortalEntry Retrieved From: https://play-lh.googleusercontent.com/ccDYfiglDLf6RuicG_QLGjiz6d3YRH_S2cbOIxE2XhkmGmze3nK9UV-Tp8du7PzHZTs
 * BarrierTape Retrieved From: https://www.blackwoods.com.au/safety-site-environmental/pedestrian-control-barriers/barrier-tapes-standard-prosafe/tape-barrier-blk-yel-75mmx300m/p/03262512
 *********************************************************************************/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h> 
#include <iostream>

#define PI 3.14159265

// Box coordinate with 36 vertices.
// Every 3 coordinates will form 1 triangle.
// The last 2 columns represent texture coordinate for mapping.
float world_vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
//GUI Uses different VBO which is provided by this array of positions
float gui_vertices[] = { -1, 1, -1, -1, 1, 1, 1, -1 }; //GUI Uses Quads and not Triangles through GL_TRIANGLE_STRIP
	
// FORWARD DECLARATIONS
//Methods provided by LearnOpenGL
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void process_input(GLFWwindow *window);
unsigned int loadTexture(std::string path); 

//Game Methods
void sky_gen(unsigned int VAO_world, unsigned int tex_sky, unsigned int tex_no_specular, Shader world_shader);
void grass_gen(unsigned int VAO_world, unsigned int tex_grass, unsigned int tex_no_specular, Shader world_shader);
void creeper_gen(unsigned int VAO_world, unsigned int tex_creeper_head, unsigned int tex_creeper_body,
				 unsigned int tex_creeper_feet, unsigned int tex_no_specular, Shader world_shader);
void random_tree_gen(unsigned int woodTex , unsigned int leavesTex, unsigned int noSpecTex , Shader ourShader, 
					 unsigned int VAO_world, int i);
void portal_gen(unsigned int VAO_world, unsigned int tex_obsidian_diffuse, unsigned int tex_obsidian_specular, 
				Shader world_shader);
void mysterious_man_gen(unsigned int VAO_world, unsigned int tex_man_face, unsigned int tex_man_body, 
					    unsigned int tex_man_arm, unsigned int tex_man_leg,unsigned int tex_no_specular, Shader world_shader);
void torch_gen(unsigned int VAO_world, unsigned int VAO_light, unsigned int tex_metal, unsigned int tex_metal_specular,
			   unsigned int tex_white, unsigned int tex_no_specular, Shader world_shader, Shader torch_shader);
void hammer_gen(int hammerIdx, float xVal, float yVal, float zVal, unsigned int VAO_world, unsigned int tex_wood, 
				unsigned int tex_metal, unsigned int tex_metal_specular, unsigned int tex_no_specular,Shader world_shader);
void portal_entry_gen(unsigned int VAO_world, unsigned int tex_portal_entry, unsigned int tex_no_specular,Shader world_shader);
void tape_barrier_gen(unsigned int VAO_world, unsigned int tex_tape_barrier, unsigned int tex_tape_barrier_specular,Shader world_shader);
void gui_hammer_gen(unsigned int VAO_gui, unsigned int VBO_gui, unsigned int tex_hammer_0, unsigned int tex_hammer_1, 
				unsigned int tex_hammer_2,unsigned int tex_hammer_3,unsigned int tex_hammer_4, unsigned int tex_hammer_5, Shader gui_shader);
void display_gui_element(unsigned int VAO_gui, unsigned int VBO_gui, unsigned int texture, Shader gui_shader);
float rand_float(float min, float max);
void toggle_hammer_pick_up(int num);
void toggle_torch_pick_up();
void toggle_man_distance();
void toggle_creeper_distance();
void toggle_portal_distance();
bool limit_map_check();
bool jump();
float calculate_angle(float xVal, float zVal);
void restart_game();

//GLOBAL VARIABLES
// Camera
glm::vec3 startPlayerPos = glm::vec3(0.0f, 1.75f, 0.0f);
Camera camera(glm::vec3(0.0f, 1.75f, 0.0f));
glm::mat4 projection, view; 

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool ORTHO_VIEW = false;
bool LOSE = false;
bool WIN = false;

// Timing
float delta_time = 0.0f; //Time between current frame and last frame
float last_frame = 0.0f;
int BRIGHTNESS_DELAY = 0;
int ORTHO_DELAY = 0;
int MAN_TAP_DELAY = 0;
int RESTART_DELAY = 0;

// Lighting
float cutOff = 12.5f;
float outerCutOff = 17.5f;
int atten_idx = 5; //Index to be used to select array 
bool atten_toggle = false;
float ambX = 1.0f;
float ambY = 1.0f;
float ambZ = 1.0f;
//Values retrieved from LearnOpenGL/Lighting/Light Casters. https://learnopengl.com/Lighting/Light-casters
const float linear_vals[12] = { 0.0014f, 0.007f, 0.014f, 0.022f, 0.027f, 0.045f, 0.07f, 0.09f, 0.14f, 0.22f, 0.35f, 0.7f };
const float quadratic_vals[12] = { 0.000007f, 0.0002f, 0.0007f, 0.0019f, 0.0028f, 0.0075f, 0.017f, 0.032f, 0.07f, 0.20f, 0.44f, 1.8f };

//Torch Values
bool picked_torch = false;
glm::vec3 light_pos(5.0f, 0.15f, 5.0f);

//Hammer Values
const float hammer_xVals[5] = { 6.0f, -27.0f, -28.0f, -28.0f, -14.0f };
const float hammer_yVal = 0.20f;
const float hammer_zVals[5] = { 9.80f, 34.80f, -39.90f, -10.90f, -2.90f };
bool hammer_toggles[5] = { false, false, false, false, false };
int hammer_pick_count = 0;
float hammer_translate_y = 0.0f;
float hammer_rotate_y = 0.0f;

bool MAN_CLOSE_ENOUGH = false;
bool CREATE_PORTAL = false;
float scale_entry_y = 0.0f;
float scale_entry_z = 0.0f;

//Transformation Arrays for Objects in Game
//Creeper (1 Head, 1 Body, 1 Leg)
glm::vec3 creeper_scales[] = {
	glm::vec3( 2.0f,  2.0f,    2.0f), //Head
	glm::vec3( 1.75f,  2.25f,   1.5f), //Body
	glm::vec3( 1.95f,  0.75f,  2.0f), //Leg
};
glm::vec3 creeper_positions[] = {
	glm::vec3( 48.0f,  3.98f,   -48.5f), //Head
	glm::vec3( 48.0f,  1.85f,   -48.5f), //Body
	glm::vec3( 48.0f,  0.38f,   -48.5f), //Leg
};

//Mysterious Man 
glm::vec3 man_scales[] = {
	glm::vec3( 1.00f,  1.00f,  1.00f), //Head
	glm::vec3( 1.00f,  1.50f,  1.25f), //Body
	glm::vec3( 0.75f,  1.25f,  0.5f), // Left Arm
	glm::vec3( 0.75f,  1.25f,   0.5f), // Right Arm
	glm::vec3( 0.75f,  1.25f,  0.5f), // Left Leg
	glm::vec3( 0.75f,  1.25f,  0.5f) // Right Leg
};
glm::vec3 man_positions[] = {
	glm::vec3( -35.0f  ,  3.25f ,  7.0f), //Head	
	glm::vec3( -35.0f  ,  2.00f ,  7.0f), //Body
	glm::vec3( -35.0f  ,  2.13f ,  7.75f), // Left Arm
	glm::vec3( -35.0f  ,  2.13f ,  6.25f), // Right Arm
	glm::vec3( -35.0f  ,  0.63f ,  7.30f), // Left Leg
	glm::vec3( -35.0f  ,  0.63f ,  6.72f) // Right Leg
};

//Map Barrier	
glm::vec3 barrier_scales[] = {
	glm::vec3( 	100.0f, 1.0f,   0.01f),	
	glm::vec3( 	100.0f, 1.0f,   0.01f),	
	glm::vec3( 	 0.01f, 1.0f,  100.0f),	
	glm::vec3(   0.01f, 1.0f,  100.0f),	
};
glm::vec3 barrier_positions[] = {
	glm::vec3( 	 0.0f, 1.65f,  50.0f),	
	glm::vec3( 	 0.0f, 1.65f, -50.0f),	
	glm::vec3(  50.0f, 1.65f,   0.0f),	
	glm::vec3( -50.0f, 1.65f,   0.0f),	
};

//TORCH
glm::vec3 torch_scales[] = {
	glm::vec3( 0.30f,  0.30f,  0.30f), //Torch Front
	glm::vec3( 0.60f,  0.20f,  0.20f), //Torch Body
};
glm::vec3 torch_positions[] = {
	glm::vec3( 	5.0f , 0.15f , 5.0f), //Torch Front	
	glm::vec3( 	5.42f, 0.15f , 5.0f), //Torch Body
};

//Portal
glm::vec3 portal_positions[] = {
	glm::vec3( -35.0f  ,  0.5f ,  0.0f),	// Bottom of Portal
	glm::vec3( -35.0f  ,  0.5f ,  1.0f),	
	glm::vec3( -35.0f  ,  0.5f ,  2.0f),	
	glm::vec3( -35.0f  ,  0.5f ,  3.0f),	
	glm::vec3( -35.0f  ,  0.5f ,  4.0f),	
	
	glm::vec3( -35.0f  ,  1.5f ,  4.0f),	// Right Side of Portal
	glm::vec3( -35.0f  ,  2.5f ,  4.0f),	
	glm::vec3( -35.0f  ,  3.5f ,  4.0f),	
	glm::vec3( -35.0f  ,  4.5f ,  4.0f),
	glm::vec3( -35.0f  ,  5.5f ,  4.0f),
	
	glm::vec3( -35.0f  ,  1.5f ,  0.0f),	// Left Side of Portal
	glm::vec3( -35.0f  ,  2.5f ,  0.0f),	
	glm::vec3( -35.0f  ,  3.5f ,  0.0f),	
	glm::vec3( -35.0f  ,  4.5f ,  0.0f),	
	glm::vec3( -35.0f  ,  5.5f ,  0.0f),	
	
	glm::vec3( -35.0f  ,  5.5f ,  1.0f),	// Top of Portal
	glm::vec3( -35.0f  ,  5.5f ,  2.0f),	
	glm::vec3( -35.0f  ,  5.5f ,  3.0f)	
};

// Countdown until the button trigger can be pressed again.
// This prevents accidental burst repeat clicking of the key.
void update_delay()
{
	if(BRIGHTNESS_DELAY > 0) BRIGHTNESS_DELAY -= 1;
	if(ORTHO_DELAY > 0) ORTHO_DELAY -= 1;
	if(MAN_TAP_DELAY > 0) MAN_TAP_DELAY -= 1;
	if(RESTART_DELAY > 0) RESTART_DELAY -= 1;
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Very Good Slender Man Game", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader programs
    // ------------------------------------
	Shader world_shader("./world.vs", "./world.fs");
	Shader torch_shader("./torch.vs", "./torch.fs");
	Shader gui_shader("./gui.vs", "./gui.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	unsigned int VBO_world, VAO_world; //World's VBO and VAO

	glGenVertexArrays(1, &VAO_world);
	glGenBuffers(1, &VBO_world);
	glBindVertexArray(VAO_world);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_world);
	glBufferData(GL_ARRAY_BUFFER, sizeof(world_vertices), world_vertices, GL_STATIC_DRAW);

	//Vertex coordinates
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//Normal vectors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//Texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//Configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int VAO_light;
	glGenVertexArrays(1, &VAO_light);
	glBindVertexArray(VAO_light);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_world);
	//Note that we update the torch's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// VAO and VBO set up for GUI (Uses quads as opposed to regular triangles and so therefore needs new VBO)
	unsigned int VAO_gui, VBO_gui;
	glGenVertexArrays(1, &VAO_gui);
	glGenBuffers(1, &VBO_gui);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_gui);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gui_vertices), gui_vertices, GL_STATIC_DRAW);
	glBindVertexArray(VAO_gui);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
    // Load and create textures 
	// -------------------------
	unsigned int tex_sky, tex_grass, tex_creeper_head, tex_creeper_body, tex_creeper_feet, tex_tree_wood, tex_tree_leaves; 
	unsigned int tex_obisdian, tex_man_face, tex_man_body, tex_man_arm, tex_man_leg, tex_metal, tex_white, tex_wood; 
	unsigned int tex_no_specular, tex_obsidian_specular, tex_metal_specular, tex_portal_entry, tex_tape_barrier;
	unsigned int tex_tape_barrier_specular, tex_win_screen, tex_lose_screen, tex_hammer_0, tex_hammer_1, tex_hammer_2;
	unsigned int tex_hammer_3, tex_hammer_4, tex_hammer_5;

	tex_sky = loadTexture("resources/textures/night_sky.jpg");
	tex_grass = loadTexture("resources/textures/mc_grass.png");
	tex_creeper_head = loadTexture("resources/textures/creeperFace.png");
	tex_creeper_body = loadTexture("resources/textures/creeperBody.png");
	tex_creeper_feet = loadTexture("resources/textures/creeperFeet.png");
	tex_tree_wood = loadTexture("resources/textures/treeWood.png");
	tex_tree_leaves = loadTexture("resources/textures/leaves.png");	
	tex_obisdian = loadTexture("resources/textures/obsidian.png");	
	tex_man_face = loadTexture("resources/textures/manFace.png");	
	tex_man_body = loadTexture("resources/textures/manBody.png");	
	tex_man_arm = loadTexture("resources/textures/manArm.png");	
	tex_man_leg = loadTexture("resources/textures/manLeg.png");
	tex_no_specular = loadTexture("resources/textures/no_specular.jpg");
	tex_obsidian_specular = loadTexture("resources/textures/obsidian_specular.jpg");
	tex_metal = loadTexture("resources/textures/metal.png");
	tex_metal_specular = loadTexture("resources/textures/metal_specular.jpg");
	tex_white = loadTexture("resources/textures/white.jpg");
	tex_wood = loadTexture("resources/textures/wood2.jpg");
	tex_portal_entry = loadTexture("resources/textures/portalEntry.png");
	tex_tape_barrier = loadTexture("resources/textures/barrierTape.jpg");
	tex_tape_barrier_specular = loadTexture("resources/textures/barrierTape_specular.png");
	tex_win_screen = loadTexture("resources/textures/win_screen.png");
	tex_lose_screen = loadTexture("resources/textures/lose_screen.png");
	tex_hammer_0 = loadTexture("resources/textures/hammer_0.png");
	tex_hammer_1 = loadTexture("resources/textures/hammer_1.png");
	tex_hammer_2 = loadTexture("resources/textures/hammer_2.png");
	tex_hammer_3 = loadTexture("resources/textures/hammer_3.png");
	tex_hammer_4 = loadTexture("resources/textures/hammer_4.png");
	tex_hammer_5 = loadTexture("resources/textures/hammer_5.png");

	//World shader configuration ----------------------------------------------------------------------------------------
	world_shader.use();
	world_shader.setInt("material.diffuse", 0);
	world_shader.setInt("material.specular", 1);

	//Declare transformation matrices
	glm::mat4 world_model, light_model, gui_model;

    // The render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
		// Per-frame time logic
		// --------------------
		float current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;

		// Updates any delay for any toggles such as brightness of the world
		update_delay();

		// Input
		// -----
		process_input(window);

		// Render
		// ------
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

		//Sets Projection to whatever is currently active (Orthographic/Perspective)
		if(ORTHO_VIEW == true)
		{
			projection = glm::ortho(-10.0f, 10.0f, -2.0f, 10.0f, -1.0f, 200.0f);
		}
		else
		{
			projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 300.0f);
		}

		// Activate main world shader
		world_shader.use();
		world_shader.setMat4("projection", projection);
		if(picked_torch == true)
		{
			world_shader.setVec3("light.direction", camera.Front); //Set light direction infront of camera
		}
		else
		{
			world_shader.setVec3("light.direction", glm::vec3(-1,0,0)); //Set light direction infront of torch on ground
		}

		world_shader.setVec3("light.position", light_pos); //Set light position
		world_shader.setFloat("light.cutOff", glm::cos(glm::radians(cutOff)));
		world_shader.setFloat("light.outerCutOff", glm::cos(glm::radians(outerCutOff)));
		world_shader.setVec3("viewPos", camera.Position); //Set current camera position 

		//Light properties
		world_shader.setVec3("light.ambient", ambX, ambY, ambZ); //Set ambient values. (World Light)
		world_shader.setVec3("light.diffuse", 3.5f, 3.5f, 3.5f); //Set diffuse values. 
		world_shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f); //Set specular values.
		world_shader.setFloat("light.constant", 1.0f); //Lighting constant 
		world_shader.setFloat("light.linear", linear_vals[atten_idx]); //Default Linear Value (Selected from LearnOpenGL)
		world_shader.setFloat("light.quadratic", quadratic_vals[atten_idx]); //Default Quadratic Value (Selected from LearnOpenGL)
		world_shader.setFloat("material.shininess", 64.0f); //Set material shininess values. 

		// Camera/View transformation
		view = camera.GetViewMatrix();
		world_shader.setMat4("view", view);

		//Draw objects
		//-----------------------------------------------------------------------------------------
		sky_gen(VAO_world, tex_sky, tex_no_specular, world_shader);
		grass_gen(VAO_world, tex_grass, tex_no_specular, world_shader);

		// Tree Generator (Currently set to draw 100 trees)
		for(int i = 0; i < 100; i++)
		{
			random_tree_gen(tex_tree_wood, tex_tree_leaves, tex_no_specular, world_shader, VAO_world, i);
		}

		portal_gen(VAO_world, tex_obisdian, tex_obsidian_specular, world_shader);
		mysterious_man_gen(VAO_world,tex_man_face,tex_man_body, tex_man_arm, tex_man_leg, tex_no_specular, world_shader);
		tape_barrier_gen(VAO_world, tex_tape_barrier,tex_tape_barrier_specular, world_shader);
		
		//Creates 5 Hammers around world which will be later picked up by the player
		for(int i = 0; i < 5; i++)
		{
			hammer_gen(i,hammer_xVals[i], hammer_yVal, hammer_zVals[i], VAO_world, tex_wood, tex_metal, tex_metal_specular,tex_no_specular, world_shader);
		}

		if(WIN == false && LOSE == false) //Only display creeper, hammer count, torch & portal entry when game has not ended
		{
			creeper_gen(VAO_world,tex_creeper_head, tex_creeper_body, tex_creeper_feet, tex_no_specular, world_shader);
			torch_gen(VAO_world, VAO_light, tex_metal,tex_metal_specular,tex_white, tex_no_specular, world_shader, torch_shader);
			portal_entry_gen(VAO_world, tex_portal_entry,tex_no_specular,world_shader);

			//Renders Hammer count for user to see	
			gui_hammer_gen(VAO_gui, VBO_gui, tex_hammer_0, tex_hammer_1, tex_hammer_2,tex_hammer_3, tex_hammer_4, tex_hammer_5, gui_shader);
		}
		else if(WIN == true) //If the player has won the game, a screen will be displayed
		{
			display_gui_element(VAO_gui, VBO_gui, tex_win_screen, gui_shader);
		}
		else if(LOSE == true) //If the player has lost the game, a screen will be displayed and camera will look up as if laying on ground
		{
			camera.Pitch = 85.0f;
			camera.ProcessMouseMovement(0,0); //Makes camera pitch to update with no mouse movement
			display_gui_element(VAO_gui, VBO_gui, tex_lose_screen, gui_shader);
		}		

		// GLFW: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // De-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO_world);
	glDeleteVertexArrays(1, &VAO_light);
	glDeleteVertexArrays(1, &VAO_gui);
	glDeleteBuffers(1, &VBO_world);
	glDeleteBuffers(1, &VBO_gui);

	// GLFW: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void process_input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //ESC Key
        glfwSetWindowShouldClose(window, true);

	float camera_speed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		camera_speed = delta_time;
	else
		camera_speed = delta_time * 2;	// Double speed with "Shift" pressed

	glm::vec3 original_pos = camera.Position; //Get's camera position prior to movement for map limits check

	if(LOSE == false && WIN == false) //Prevents Player from moving once game has ended
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) //W Key
			camera.ProcessKeyboard(FORWARD, camera_speed);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) //A Key
			camera.ProcessKeyboard(LEFT, camera_speed);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) //S Key
			camera.ProcessKeyboard(BACKWARD, camera_speed);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) //D Key
			camera.ProcessKeyboard(RIGHT, camera_speed);
	}
	//Limits Player to map
	if(limit_map_check() == true) { camera.Position = original_pos; } //Puts player back to before movement
	
	//Elevates player if in nether portal
	if(jump() == true){ camera.Position.y = 2.75f; }
	else { camera.Position.y = 1.75; }

	if(picked_torch == true) //Increase/Decrease brightness radius of torch light
	{
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) //K Key
		{		
			ambX -= 0.2;
			ambY -= 0.2;
			ambZ -= 0.2;
			cutOff -= 0.5f;
			outerCutOff -= 0.5f;
		}

		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) //L Key
		{
			ambX += 0.2;
			ambY += 0.2;
			ambZ += 0.2;
			cutOff += 0.5f;
			outerCutOff += 0.5f;
		}
	}	
	//Makes world turn to Day/Night time (Changes ambient values to make it seem like day/night time)
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && BRIGHTNESS_DELAY == 0) //O Key
	{
		BRIGHTNESS_DELAY = 20;
		if(atten_toggle == true)
		{
			atten_idx = 5;
			atten_toggle = false;
		}
		else
		{
			atten_idx = 0;
			atten_toggle = true;
		}
	}
    
	//Toggle Parallel(Orthographic)/ Perspective View For Game
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && ORTHO_DELAY == 0) //P Key
	{
		ORTHO_DELAY = 20;
		if(ORTHO_VIEW == true)
		{
			ORTHO_VIEW = false;
		}
		else
		{
			ORTHO_VIEW = true;
		}
	}

	//Interact With Person to give hammers to person
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && MAN_TAP_DELAY == 0 && MAN_CLOSE_ENOUGH == true) //G Key
	{
		MAN_TAP_DELAY = 20;
		if(hammer_pick_count == 5) { CREATE_PORTAL = true; }
		else { CREATE_PORTAL = false; }
	}
	
	//Restart Game
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && RESTART_DELAY == 0) //R Key
	{
		RESTART_DELAY = 20;
		restart_game();
	}

}

// GLFW: Whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// GLFW: Whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

	if(WIN == false && LOSE == false)
	{
    	camera.ProcessMouseMovement(xoffset, yoffset);
	}
}

// GLFW: Whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

//Registering a new texture.
unsigned int loadTexture(std::string path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load(FileSystem::getPath(path).c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

void sky_gen(unsigned int VAO_world, unsigned int tex_sky, unsigned int tex_no_specular, Shader world_shader)
{
	//Sky
	glBindVertexArray(VAO_world);//This does not have to binded every time after first call, but just for consistency.

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_sky);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex_no_specular);

	glm::mat4 world_model = glm::mat4();
	world_model = glm::scale(world_model, glm::vec3(150.0f, 150.0f, 150.0f));
	world_shader.setMat4("model", world_model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void grass_gen(unsigned int VAO_world, unsigned int tex_grass, unsigned int tex_no_specular, Shader world_shader)
{
	//Grass
	glBindVertexArray(VAO_world);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_grass);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex_no_specular);

	glm::mat4 world_model = glm::mat4();
	world_model = glm::translate(world_model, glm::vec3(0.0f, -0.5f , 0.0f));
	world_model = glm::scale(world_model, glm::vec3(100.0f, 1.0f, 100.0f));
	world_shader.setMat4("model", world_model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

//Renders Creeper (Enemy character that follow the player (camera))
void creeper_gen(unsigned int VAO_world, unsigned int tex_creeper_head, unsigned int tex_creeper_body,
				 unsigned int tex_creeper_feet, unsigned int tex_no_specular, Shader world_shader)
{
	glBindVertexArray(VAO_world);

	for(int i = 0; i < 3; i++)
	{
		if(i == 0) //Head
		{ 
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_creeper_head); 
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_no_specular);
		}
		else if (i == 1) //Body
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_creeper_body); 
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_no_specular);
			
		}
		else //Leg
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_creeper_feet); 
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_no_specular);
		}

		if(picked_torch == true) //Starts movement of creeper once torch is picked up
		{
			float yVal = creeper_positions[i].y;
			float speed = 7.0 * delta_time;
			creeper_positions[i] += glm::normalize(camera.Position - creeper_positions[i]) * speed;
			creeper_positions[i].y = yVal;
		}

		//Creeper Transformations
		glm::mat4 world_model = glm::mat4(1.0f);
		world_model = glm::translate(world_model, creeper_positions[i]);
		world_model = glm::scale(world_model, creeper_scales[i]);
		world_model = glm::rotate(world_model, glm::radians(calculate_angle(creeper_positions[i].x, creeper_positions[i].z)), glm::vec3(0,1,0));
		world_shader.setMat4("model", world_model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	toggle_creeper_distance(); //Checks if creeper is close to player (Game lose check)
}

//Renders a single tree with its trunk and leaves
void random_tree_gen(unsigned int tex_tree_wood , unsigned int tex_tree_leaves, unsigned int tex_no_specular, 
					 Shader world_shader, unsigned int VAO_world, int i)
{
	srand(i); //First tree will always remain as the first tree seed and so it doesn't move throughout game 
	int xVal = rand_float(-50.0f, 50.0f); //Limits tree x location to inside map
	int zVal = rand_float(-50.0f, 50.0f); //Limits tree z location to inside map

	glBindVertexArray(VAO_world);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_tree_wood);

	//Tree log/trunk transformations
	glm::mat4 world_model = glm::mat4();
	world_model = glm::translate(world_model, glm:: vec3(xVal, 5.0f, zVal));
	world_model = glm::scale(world_model, glm::vec3(1.5f, 10.0f, 1.5f));
	world_shader.setMat4("model", world_model);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//Tree Leaves position matrix
	glm::vec3 tree_leaves_positions[] = {
			glm::vec3( xVal,          10.5f,           zVal),
			glm::vec3( xVal,           9.5f,   zVal - 1.65f),
			glm::vec3( xVal + 1.65f,   9.5f,           zVal),
			glm::vec3( xVal,           9.5f,   zVal + 1.65f),
			glm::vec3( xVal - 1.65f,   9.5f,           zVal),
	};

	glBindVertexArray(VAO_world);		
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_tree_leaves);
	//Each tree gets 5 leaves
	for(int i = 0; i < 5; i++)
	{
		//Tree leaves transformation		
		world_model = glm::mat4();
		world_model = glm::translate(world_model, tree_leaves_positions[i]);
		world_model = glm::scale(world_model, glm::vec3(1.75f, 1.75f, 1.75f));
		world_shader.setMat4("model", world_model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

//Method that renders the portal
void portal_gen(unsigned int VAO_world, unsigned int tex_obsidian_diffuse, unsigned int tex_obsidian_specular, Shader world_shader)
{
	glBindVertexArray(VAO_world);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_obsidian_diffuse);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex_obsidian_specular);

	glm::mat4 world_model;
	for(int i = 0; i < 18; i++)
	{
		//Portal Blocks transformations
		world_model = glm::mat4();
		world_model = glm::translate(world_model, portal_positions[i]);
		world_model = glm::scale(world_model, glm::vec3(1.0f, 1.0f, 1.0f)); 
		world_shader.setMat4("model", world_model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

//Method that renders a man next to portal
void mysterious_man_gen(unsigned int VAO_world,unsigned int tex_man_face,unsigned int tex_man_body,unsigned int tex_man_arm,
						unsigned int tex_man_leg, unsigned int tex_no_specular, Shader world_shader)
{
	toggle_man_distance(); //Checks if player is close to man so player is able to give hammers to man
	
	glBindVertexArray(VAO_world);
	for(int i = 0; i < 6; i++)
	{
		if(i == 0) //Head of Man
		{ 
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_man_face); 
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_no_specular);
		}
		else if (i == 1) //Body of Man 
		{ 
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_man_body); 
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_no_specular);
		}
		else if (i == 2 || i == 3) //Arms of Man
		{ 
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_man_arm); 
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_no_specular);
		}
		else //Legs of Man
		{ 
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_man_leg); 
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_no_specular);
		}
		//Man transformations 
		glm::mat4 world_model;
		world_model = glm::mat4();
		world_model = glm::translate(world_model, man_positions[i]);
		world_model = glm::scale(world_model, man_scales[i]); 
		world_model = glm::rotate(world_model, glm::radians(90.0f) ,glm::vec3(0.0f, 1.0f, 0.0f));
		world_shader.setMat4("model", world_model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

//Method that renders the torch of the game
void torch_gen(unsigned int VAO_world, unsigned int VAO_light, unsigned int tex_metal, unsigned int tex_metal_specular,
			   unsigned int tex_white, unsigned int tex_no_specular, Shader world_shader, Shader torch_shader)
{
	glm::mat4 world_model;
	glm::mat4 light_model;
	
	toggle_torch_pick_up(); //Checks if camera is next to torch so player can pick it up
	for(int i = 0; i < 2; i++)
	{
		if(i == 0) //Torch Front/Head
		{					
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_white); 
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_no_specular);
		}
		else //Torch Handle
		{
			glBindVertexArray(VAO_world);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_metal); 
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_metal_specular);
		}

		world_model = glm::mat4();
		if(picked_torch == true && i == 0) //If the torch has been picked up the torch will be infront of camera
		{					
			//set light to be in front of player at all times
			light_pos = camera.Position + camera.Front;
				
			float angle = calculate_angle(light_pos.x, light_pos.z); //Get's rotation angle
			torch_shader.use(); //Uses torch_shader so that object does not get affected by its own light
			torch_shader.setMat4("projection", projection);
			torch_shader.setMat4("view", view);
			
			//Torch Transformations
			light_model = glm::mat4();
			light_model = glm::translate(light_model, light_pos);
			light_model = glm::scale(light_model, torch_scales[i]);
			light_model = glm::translate(light_model, glm::vec3(0.0,-1.5f, 0.0));
			light_model = glm::rotate(light_model, glm::radians(angle), glm::vec3(0,1,0));
			torch_shader.setMat4("model", light_model);
			glBindVertexArray(VAO_light);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		else if (picked_torch == false) //Render normal torch on ground (Not Picked Up)
		{
			//Torch Transformations
			world_model = glm::translate(world_model, torch_positions[i]);
			world_model = glm::scale(world_model, torch_scales[i]);
			world_shader.setMat4("model", world_model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
}

//Method that renders a single hammer
void hammer_gen(int hammerIdx, float xVal, float yVal, float zVal, unsigned int VAO_world, unsigned int tex_wood, 
				unsigned int tex_metal, unsigned int tex_metal_specular, unsigned int tex_no_specular, Shader world_shader)
{
	toggle_hammer_pick_up(hammerIdx); //Checks if player is close to hammer
	//Animation values
	hammer_translate_y += 0.5f; //Translates by 0.5 (Speed)
	hammer_rotate_y += 0.5f; //Rotates by 0.5 (Speed)
	if(abs(hammer_translate_y - 360.0f) <= 0.1f) hammer_translate_y = 0.0f;
	if(abs(hammer_rotate_y - 360.0f) <= 0.1f) hammer_rotate_y = 0.0f;

	if(!hammer_toggles[hammerIdx]) //Only render hammer if it is not picked up
	{
		for(int i = 0; i < 2; i++)
		{
			glm::mat4 world_model = glm::mat4();
			world_shader.use();
			if(i == 0) //Metal Head of Hammer
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tex_metal); 
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, tex_metal_specular);
				world_model = glm::translate(world_model, glm::vec3(xVal, yVal + (0.1f * sin(hammer_translate_y * PI / 180.f)), zVal));
				world_model = glm::rotate(world_model, glm::radians(hammer_rotate_y), glm::vec3(0.0f, 1.0f, 0.0f));
				world_model = glm::scale(world_model, glm::vec3(0.6f, 0.2f, 0.2f));
			}
			else if ( i == 1) //Wooden Hammer Handle
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tex_wood); 
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, tex_no_specular);
				world_model = glm::translate(world_model, glm::vec3(xVal, yVal + (0.1f * sin(hammer_translate_y * PI / 180.f)) + 0.5, zVal));
				world_model = glm::rotate(world_model, glm::radians(hammer_rotate_y), glm::vec3(0.0f, 1.0f, 0.0f));
				world_model = glm::scale(world_model, glm::vec3(0.2f, 0.8f, 0.2f));
			}
			world_shader.setMat4("model", world_model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
}

//Method that renders portal entry (Purple Texture)
void portal_entry_gen(unsigned int VAO_world, unsigned int tex_portal_entry, unsigned int tex_no_specular, 
						 Shader world_shader)
{
	glm::mat4 world_model;
	world_shader.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_portal_entry); 
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex_no_specular);

	if(CREATE_PORTAL) //If Create Portal is true that means the hammers have all been collected and given to man
	{
		//Animate portal entry opening
		scale_entry_y += 0.1f;
		scale_entry_z += 0.1f;
		if(scale_entry_y >= 4.0f ) { scale_entry_y = 4.0f; } //Maximum y scale value to expand
		if(scale_entry_z >= 3.0f ) { scale_entry_z = 3.0f; } //Maximum z scale value to expand
		toggle_portal_distance(); //Check if player is next to portal (Only checks if portal entry is created)
	}

	//Portal Entry Transformations
	world_model = glm::translate(world_model, glm::vec3(-35.0f, 3.0f, 2.0f));
	world_model = glm::scale(world_model, glm::vec3(0.2f, scale_entry_y, scale_entry_z)); //Small
	world_shader.setMat4("model", world_model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

//Method that renders map barriers 
void tape_barrier_gen(unsigned int VAO_world, unsigned int tex_tape_barrier, unsigned int tex_tape_barrier_specular, 
						 Shader world_shader)
{
	world_shader.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_tape_barrier); 
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex_tape_barrier_specular);

	for(int i; i < 4; i++)
	{	
		//Map tape barrier transformations
		glm::mat4 world_model;
		world_model = glm::translate(world_model, barrier_positions[i]);
		world_model = glm::scale(world_model, barrier_scales[i]);
		world_shader.setMat4("model", world_model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

//Method that displays amount of hammers player currently has picked up through GUI 
void gui_hammer_gen(unsigned int VAO_gui, unsigned int VBO_gui, unsigned int tex_hammer_0, unsigned int tex_hammer_1, 
				unsigned int tex_hammer_2,unsigned int tex_hammer_3,unsigned int tex_hammer_4,
				unsigned int tex_hammer_5,Shader gui_shader)
{
	if(hammer_pick_count == 0) { display_gui_element(VAO_gui, VBO_gui, tex_hammer_0, gui_shader); }
	else if(hammer_pick_count == 1) { display_gui_element(VAO_gui, VBO_gui, tex_hammer_1, gui_shader); }
	else if(hammer_pick_count == 2) { display_gui_element(VAO_gui, VBO_gui, tex_hammer_2, gui_shader); }
	else if(hammer_pick_count == 3) { display_gui_element(VAO_gui, VBO_gui, tex_hammer_3, gui_shader); } 
	else if(hammer_pick_count == 4) { display_gui_element(VAO_gui, VBO_gui, tex_hammer_4, gui_shader); } 
	else if(hammer_pick_count == 5) { display_gui_element(VAO_gui, VBO_gui, tex_hammer_5, gui_shader); }
}

//Method that displays GUI Element
void display_gui_element(unsigned int VAO_gui, unsigned int VBO_gui, unsigned int texture, Shader gui_shader)
{
	glm::mat4 gui_model;	
	gui_shader.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_gui);
	glBindVertexArray(VAO_gui);

	gui_model = glm::mat4(1.0f);
	gui_shader.setMat4("tMatrix", gui_model);
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); //Not using triangles but using quads (gui_vertices array)
	glDisable(GL_BLEND);
}

//Method that restarts current game session
void restart_game()
{
	//All values are back to their default values from when the game has started
	ORTHO_VIEW = false;
	WIN = false;
	LOSE = false;
	camera.Position = startPlayerPos;
	camera.Pitch = 0.0f;
	camera.ProcessMouseMovement(0, 0); //Makes camera pitch to update with no mouse movement
	BRIGHTNESS_DELAY = 0;
	ORTHO_DELAY = 0;
	MAN_TAP_DELAY = 0;
	atten_idx = 5; 
	atten_toggle = false;
	ambX = 1.0f;
	ambY = 1.0f;
	ambZ = 1.0f;
	picked_torch = false;
	light_pos = glm::vec3(5.0f, 0.15f, 5.0f);

	for(int i = 0; i < 5; i++) //Resets all hammer toggles to false 
	{
		hammer_toggles[i] = false;
	}
	hammer_pick_count = 0;
	MAN_CLOSE_ENOUGH = false;
	CREATE_PORTAL = false;
	scale_entry_y = 0.0f;
	scale_entry_z = 0.0f;

	//Resets Values of Creeper Position to default since it could've moved in previous session
	creeper_positions[0] = { glm::vec3( 48.0f,  3.98f,   -48.5f)};
	creeper_positions[1] = { glm::vec3( 48.0f,  1.85f,   -48.5f)};
	creeper_positions[2] = { glm::vec3( 48.0f,  0.38f,   -48.5f)};
}

//Method that allows user to "jump" onto nether portal to win game
bool jump()
{
	bool jump = false;
	//Checks is player is within the nether portal blocks
	if(((-34.0f >= camera.Position.x) && (-36.0f <= camera.Position.x )) && ((1.0f <= camera.Position.z) && (camera.Position.z <= 3.0f)))
	{
		jump = true; 
	}
	return jump;
}

//Method that checks if player is out of map (Limits player to map boundaries)
bool limit_map_check()
{
	bool out_of_map = false;
	if(camera.Position.x > 49.9f || camera.Position.z > 49.9f || camera.Position.x < -49.9f || camera.Position.z < -49.9f)
	{
		out_of_map = true;
	}
	return out_of_map;
}

//Method that checks if player is close enough to torch to pick it up
void toggle_torch_pick_up()
{
	glm::vec3 torchPos = torch_positions[0]; //Torch Head is torch position
	if (glm::length(camera.Position - torchPos) < 2.5f && !picked_torch)
	{
		picked_torch = true;
	}
}

//Method that checks if player is close enough to hammer to pick it up
void toggle_hammer_pick_up(int num)
{
	glm::vec3 hammerPos = glm::vec3(hammer_xVals[num], hammer_yVal, hammer_zVals[num]);
	if (glm::length(camera.Position - hammerPos) < 2.5f && !hammer_toggles[num])
	{
		hammer_toggles[num] = true; //Makes current hammer picked up value to true so that it doesn't render again
		hammer_pick_count += 1; //Once hammer is picked up it will increment hammer count (Total of 5)
	}
}

//Method that checks if creeper is close to player (Game lose check)
void toggle_creeper_distance()
{
	//Uses Creeper Body Vector with height same as camera
	glm::vec3 creeper_pos = creeper_positions[1];
	creeper_pos.y = 1.75f;
	if(glm::length(camera.Position - creeper_pos) <= 4.0f)
		LOSE = true;
	else
		LOSE = false;
}

//Method that checks if player is close to the man next to portal
void toggle_man_distance()
{
	//Uses Man Body Vector with height same as camera
	glm::vec3 man_pos = man_positions[1];
	man_pos.y = 1.75f;
	if(glm::length(camera.Position - man_pos) <= 5.0f)
		MAN_CLOSE_ENOUGH = true;
	else
		MAN_CLOSE_ENOUGH = false;
}

//Method that checks if player is close to portal entry (Game win Check)
void toggle_portal_distance()
{
	glm::vec3 portal_pos = glm::vec3(-35.0f, 2.75f, 2.0f);
	if(glm::length(camera.Position - portal_pos) <= 0.5f)
		WIN = true;
	else
		WIN = false;
}

//Method that provides a random float number within a specified range
float rand_float(float min, float max)
{
	float num = rand() / (float) RAND_MAX;
	return min + num * ( max - min ); 
}

//Method that calcaultes angle in order to allow provided object to face player (camera)
float calculate_angle(float xVal, float zVal)
{
	//Get difference of x and z co-ords provided from object to player
	float x_diff = camera.Position.x - xVal; 
	float z_diff = camera.Position.z - zVal; 
	float angle = glm::degrees(atan2(x_diff, z_diff)); //Convert to degrees 
	return angle; 
}
