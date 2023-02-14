# Introduction :

**Ray-casting** : is a rendering technique to create a 3D perspective in a 2D map. Back when computers were slower it wasn't possible to run real 3D engines in realtime, and ray-casting was the first solution. Ray-casting can go very fast, because only a calculation has to be done for every vertical line of the screen. The most well known game that used this technique, is of course Wolfenstein 3D.


**Ray-tracing** : is a lighting technique that brings an extra level of realism to games. It emulates the way light reflects and refracts in the real world, providing a more believable environment than what’s typically seen using static lighting in more traditional games.

### **Ray-casting vs Ray-tracing :**

Ray-casting :

- Rays are cast and traced (تتبع)in groups
- in a 320x200 display resolution a ray-caster traces only 320 rays (أشعة)
- Fast rendering (استدعاء)
- Resulting image is not very realistic
- a viable option for real-time rendering

Ray-Tracing :

- Each ray is traced separately, so each point (usually a pixel) is traced by one single ray
- In a 320x200 display resolution a ray-tracer needs to trace 64,000 rays
- slow rendering
- Resulting image is extremely realistic
- Not a viable option for real-time rendering

## Ray-casting Limitations :

- Walls are always perpendicular (عمودي) (90-degree angle) with the floor
- Floor is always flat
- Walls are made of cubes that have the same size (square grid only) (شبكة مربعة فقط)

# Trigonometry :

**Degrees and Radians :** 

**Degrees :** 

0 degree to 360 degree

**Radians :** 

The **Radian** is a pure measure based on the **Radius** of the circle

In classical geometry, a radius of a circle or sphere is any of the line segments from its center to its perimeter, and in more modern usage, it is also their length.

1 radian = 57.2958 degree

Dimension (البعد) of the projection plane : 320 * 200

Distance between rays : 60 degree / 320

```c
const FOV_ANGLE = 60 * (Math.PI / 180); // Radians (زاوية الرؤية)
const NUM_RAYS = 320 // RAYS(columns)
rayAngle += FOV_ANGLE / NUM_RAYS;
```

# **What is field of view?**

FOV stands for field of view, or field of vision. This is the range of what a user can see. For example, your FOV in a video game is how much of a given level you can see on your screen at once. Meanwhile, your FOV when wearing a VR headset determines how much of the landscape ahead of you is visible when you’re wearing the headset.

**Field of view** is the extent of the observable world that is seen at a given time either through someone's eyes, on a display screen, or through the viewfinder on a camera. Field of view (FOV) also describes the angle through which one can see that observable world. It refers to the coverage of an entire area, rather than a fixed focal point.

In humans, the average field of view is about 170-180 degrees. This is often hard to accomplish through gaming or optical devices. The wider the field of view, the more one can see of that observable world.

## Sine Cosine and Tangent :

A right-angled triangle is a triangle in which one of the angles is a right-angle. The hypotenuse of a right angled triangle is the longest side, which is the one opposite the right angle. The adjacent side is the side which is between the angle in question and the right angle. The opposite side is opposite the angle in question.

$$
tan(30degree) = 160 / adjacent
$$

$$
adjacent = 160 / tan(30degree) = 277.13
$$

Dimension of the projection plane : 320 * 200

Distance from player to projection plane : 277.13 units/pixels 

**Pythagorean theorem :**

$$
hypotenuse² = opposite² + adjacent²
$$

```c
distanceAB = sqrt((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
```

# Defining the 2D Map Grid :

## Defining the Map :

i & j is variables 

### Ray-casting in Cub3D :

1. Substract 30 degrees from the player rotation angle (FOV/2)
2. start at column 0
3. **While** (column < 320)
    1. cast a rat
    2. Trace the ray until it intersects with a wall (`map[i][j] == 1`)
    3. Record the intersection (x,y) and the distance (ray length)
    4. Add the angle increment so the ray moves to the right
        
        rayAngle += 60 /320 (زاوية الشعاع)
    
    ```jsx
    function castallRays()
    {
    		var columnId = 0;
    		
    		// start first ray substracting half of the FOV
    		var rayAngle  = player.rotationAngle - (FOV_ANGLE / 2);
    		
    		// Loop all columns casting rays
    		for (var i = 0; i < NUM_RAYS ; i++)
    		{
    				// call function to cast a single ray
    				var ray = new Ray(rayAngle);
    				ray.cast(columnId);
    
    				// next ray is last ray incrementes by FOV_ANGLE / NUM_RAYS
    				rayAngle += FOV_ANGLE / NUM_RAYS;
    
    				columnId++;
    		}
    }
    ```
    
    ## Finding Wall Hits :
    
    We going to learn about one of the most important details of the ray-casting technique used by Wolfenstein3D is that, once we find the first distances *delta-x* and *delta-y*, all we need to do is increment these deltas until we find a wall intersection.
    
    ![https://files.cdn.thinkific.com/file_uploads/167815/images/f80/161/a1c/DDA-deltas.jpg](https://files.cdn.thinkific.com/file_uploads/167815/images/f80/161/a1c/DDA-deltas.jpg)
    
    This technique of finding the difference and increment the same value every time is sometimes called "**DDA algorithm**."
    
    DDA stands for "*Digital Differential Analyzer*." It is an ugly name for something that is actually not that difficult. This set of algorithms deal with how we interpolate values from a *start* value to an *end* value.
    
    In our case, our DDA algorithm simply defines ***how much it should increment in each step*** and proceeds to increment the same *delta-x* and *delta-y* values for each pass of our loop. We keep incrementing until we find the wall intersection that we are looking for.
    
    I just wanted to mention the DDA algorithm because many books and articles will use this terminology and will assume that you know what they mean. It's important that we clarify these obscure terms, so we don't feel intimidated the next time we read about them.
    
    ### Distance to Wall Hit :
    
    1. The best way is to check for horizontal “|” and vertical “-” intersections separately 
    2. When there is a wall on either a vertical or horizontal intersection, the checking stops
    3. The distance to both horizontal and vertical intersection point is then compared , and we select then closest one 
    
    ### Finding Horizontal intersections :
    
    1. **Find coordinate of the first horizontal intersection (point A)**
    
    the distance Δx will always be the same for the next horizontal intersections
    
    the distance Δy will always be the same for the next vertical intersections
    
    ```jsx
    // WOLF3D source code calls these xstep and ystep
    long xstep;
    long ystep; 
    ```
    
    $$
    Ay = |Py/32| * 32
    $$
    
    $$
    Ax = Px + (Py - Ay) / tan(a)
    $$
    
    ```c
    // WOLF3D calls them xintercept and yintercept
    long xintercept;
    long yintercept;
    ```
    
    1. **Find ystep and xstep :**
    
    $$
    ystep = 32
    $$
    
    $$
    xstep = ystep / tan(a)
    $$
    
    1. **Convert intersection point (x,y) into map index[i,j] :**
    2. **********if (intersection hits a wall ):**
        
        then : store horizontal hit distance
        
        else : find next horizontal intersection
        
    
    ```c
    // HORIZONTAL intersection steps
    long ystep = TITLE_SIZE;
    long xstep = TITLE_SIZE / tan(rayAngle);
    ```
    
    ### Finding Vertical Intersections :
    
    1. **Find coordinate of the first vertical intersection (point A)**
    2. **Find xstep**
    3. **find ystep**
    4. **Convert intersection point (x,y) into map index[i,j] :**
    5. **********if (intersection hits a wall ):**
        
        then : store Vertical hit distance
        
        else : find next Vertical intersection
    
    $$
    xint ercept = (Px / Tile-size) * Tile-size
    $$
    
    $$
    xstep = 32
    $$
    
    $$
    ystep = tan(a) * xstep
    $$
    
    ```c
    // VERTICAL intersection steps
    long ystep = TITLE_SIZE;
    long xstep = TITLE_SIZE * tan(rayAngle);
    ```
    
    ## Distance from ray to wall hit :
    
    1. We have just found the first intersection with the grid (point **A**)
    2. And we also calculated Δx and Δy (aka xstep and ystep)
    3. All we have to do is loop incrementing xstep horizontally and ystep vertically until a wall (map[i][j] == 1)
    4. Get both horizontal distance and vertical distance and the closest one is our final distance from the ray to the wall

# Rendering Walls :

## wall projection :

actual wall height : 32

distance to the wall : (ray.distance)

distance from player to projection plane :

## Finding the wall strip height :

## Fishbowl Distrotion :

$$
cos(o) = correct-distance / distored-distance 
$$

```c
correctDistance = ray.distance * Math.cos(ray.rayAngle - player.rotationAngle);
```

- **MinilibX** :
    
    MiniLibX is a tiny graphics library which allows you to do the most basic things for rendering something in screens without any knowledge of X-Window and Cocoa. It provides so-called simple window creation, a questionable drawing tool, half-ass image functions and a weird event management system.
    
    # **About X-Window**
    
    X-Window is a network-oriented graphical system for unix. For example this is used when connecting to remote desktops. One of the most common examples of such implementation would be TeamViewer.
    
    # **About macOS**
    
    macOS handles the graphical access to its screen, however to access this, we must register our application to the underlying macOS graphical framework that handles the screen, windowing system, keyboard and mouse.
    
    # **Installation**
    
    ### **Compilation on macOS**
    
    Because MiniLibX requires Cocoa of MacOSX (AppKit) and OpenGL (it doesn’t use X11 anymore) we need to link them accordingly. This can cause a complicated compilation process. A basic compilation process looks as follows.
    
    For object files, you could add the following rule to your makefile, assuming that you have the `mlx` source in a directory named `mlx` in the root of your project:
    
    ```jsx
    %.o: %.c
    	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@
    ```
    
    To link with the required internal macOS API:
    
    ```jsx
    $(NAME): $(OBJ)
    	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
    ```
    
    Do mind that you need the `libmlx.dylib` in the same directory as your build target as it is a dynamic library!
    
    # **Initialization**
    
    Before we can do anything with the MiniLibX library we must include the `<mlx.h>` header to access all the functions and we should execute the `mlx_init` function. This will establish a connection to the correct graphical system and will return a `void *` which holds the location of our current MLX instance. To initialize MiniLibX one could do the following:
    
    ```c
    #include <mlx.h>
    
    int	main(void)
    {
    	void	*mlx;
    
    	mlx = mlx_init();
    }
    ```
    
    When you run the code, you can’t help but notice that nothing pops up and that nothing is being rendered. Well, this obviously has something to do with the fact that you are not creating a window yet, so let’s try initializing a tiny window which will stay open forever. You can close it by pressing CTRL + C in your terminal. To achieve this, we will simply call the `mlx_new_window` function, which will return a pointer to the window we have just created. We can give the window height, width and a title. We then will have to call `mlx_loop` to initiate the window rendering. Let’s create a window with a width of 1920, a height of 1080 and a name of “Hello world!”:
    
    ```c
    #include <mlx.h>
    
    int	main(void)
    {
    	void	*mlx;
    	void	*mlx_win;
    
    	mlx = mlx_init();
    	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    	mlx_loop(mlx);
    }
    ```
    
    ### **mlx_destroy_window**
    
    Destroys a window instance accordingly.
    
    ```c
    /*
    ** Destroy a window instance.
    **
    ** @param	void *mlx_ptr	the mlx instance;
    ** @param	void *win_ptr	the window instance;
    ** @return	int				has no return value (bc).
    */
    int		mlx_destroy_window(void *mlx_ptr, void *win_ptr);
    ```
    
    ### **mlx_clear_window**
    
    Clears the current window. This is not a recommended function to use. Instead it is recommended to use the function `mlx_put_image_to_window` with a recycled image that you have cleared.
    
    ```c
    /*
    ** Clear the provided window.
    **
    ** @param	void *mlx_ptr	the mlx instance pointer;
    ** @param	void *win_ptr	the window instance pointer;
    ** @return	int				has no return value (bc).
    */
    int		mlx_clear_window(void *mlx_ptr, void *win_ptr);
    ```
    
    # **Writing pixels to a image**
    
    Now that we have basic window management, we can get started with pushing pixels to the window. How you decide to get these pixels is up to you, however some optimized ways of doing this will be discussed. First of all, we should take into account that the `mlx_pixel_put` function is very, very slow. This is because it tries to push the pixel instantly to the window (without waiting for the frame to be entirely rendered). Because of this sole reason, we will have to buffer all of our pixels to a image, which we will then push to the window. All of this sounds very complicated, but trust me, its not too bad.
    
    First of all, we should start by understanding what type of image `mlx`requires. If we initiate an image, we will have to pass a few pointers to which it will write a few important variables. The first one is the `bpp`, also called the bits per pixel. As the pixels are basically ints, these usually are 4 bytes, however, this can differ if we are dealing with a small endian (which means we most likely are on a remote display and only have 8 bit colors).
    
    Each pixel typically consists of 8 bits (**1 byte) for a Black and White (B&W) image or 24 bits (3 bytes) for a color image**-- one byte each for Red, Green, and Blue.
    
    Now we can initialize the image with size 1920×1080 as follows:
    
    ```c
    #include <mlx.h>
    
    int	main(void)
    {
    	void	*img;
    	void	*mlx;
    
    	mlx = mlx_init();
    	img = mlx_new_image(mlx, 1920, 1080);
    }
    ```
    
    `mlx_new_image()` creates a new image in memory.
    
    It only needs the size of the image to be created, using the `width` and `height` parameters, and the `mlx_ptr` connection identifier
    
    That wasn’t too bad, was it? Now, we have an image but how exactly do we write pixels to this? For this we need to get the memory address on which we will mutate the bytes accordingly. We retrieve this address as follows:
    
    ```c
    #include <mlx.h>
    
    typedef struct	s_data {
    	void	*img;
    	char	*addr;
    	int		bits_per_pixel;
    	int		line_length;
    	int		endian;
    }				t_data;
    
    int	main(void)
    {
    	void	*mlx;
    	t_data	img;
    
    	mlx = mlx_init();
    	img.img = mlx_new_image(mlx, 1920, 1080);
    
    	/*
    	** After creating an image, we can call `mlx_get_data_addr`, we pass
    	** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
    	** then be set accordingly for the *current* data address.
    	*/
    	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
    								&img.endian);
    }
    ```
    
    Notice how we pass the `bits_per_pixel`, `line_length`and `endian`variables by reference? These will be set accordingly by MiniLibX as per described above.
    
    `mlx_get_data_addr` returns a `char *` address that represents the begining of the memory area where the image is stored.
    
    `mlx_get_data_addr()` returns information about the created image, allowing a user to modify it later.
    
    The `img_ptr` parameter specifies the image to use.
    
    The three next parameters should be the addresses of three different valid integers.
    
    `bits_per_pixel` will be filled with the number of bits needed to represent a pixel color (also called the depth of the image).
    
    `size_line` is the number of bytes used to store one line of the image in memory. This information is needed to move from one line to another in the image.
    
    `endian` tells you wether the pixel color in the image needs to be stored in:little `(endian == 0)`, or big `(endian == 1)`.
    
    From this adress, the first `bits_per_pixel` bits represent the color of the first pixel in the first line of the image.
    
    The second group of `bits_per_pixel` bits represent the second pixel of the first line, and so on.
    
    Add `size_line` to the adress to get the begining of the second line. You can reach any pixels of the image that way.
    
    `mlx_destroy_image` destroys the given image (`img_ptr`).
    
    Now we have the image address, but still no pixels. Before we start with this, we must understand that the bytes are not aligned, this means that the `line_length` differs from the actual window width. We therefore should ALWAYS calculate the memory offset using the line length set by `mlx_get_data_addr`.
    
    We can calculate it very easily by using the following formula:
    
    ```c
    int offset = (y * line_length + x * (bits_per_pixel / 8));
    ```
    
    Now that we know where to write, it becomes very easy to write a function that will mimic the behaviour of `mlx_pixel_put`but will simply be many times faster:
    
    ```c
    typedef struct	s_data {
    	void	*img;
    	char	*addr;
    	int		bits_per_pixel;
    	int		line_length;
    	int		endian;
    }				t_data;
    
    void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
    {
    	char	*dst;
    
    	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    	*(unsigned int*)dst = color;
    }
    ```
    
    # **Pushing images to a window**
    
    Now that we can finally create our image, we should also push it to the window, so that we can actually see it. This is pretty straight forward, let’s take a look at how we can write a red pixel at (5,5) and put it to our window:
    
    ```c
    #include <mlx.h>
    
    typedef struct	s_data {
    	void	*img;
    	char	*addr;
    	int		bits_per_pixel;
    	int		line_length;
    	int		endian;
    }				t_data;
    
    int	main(void)
    {
    	void	*mlx;
    	void	*mlx_win;
    	t_data	img;
    
    	mlx = mlx_init();
    	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    	img.img = mlx_new_image(mlx, 1920, 1080);
    	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
    								&img.endian);
    	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
    	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    	mlx_loop(mlx);
    }
    ```
    
    ## Events :
    
    Events are the foundation of writing interactive applications in MiniLibX.
    
    All hooks in MiniLibX are nothing more than a function that gets called whenever a event is triggered. Mastering all these events won’t be necessary, however, we will quickly go over each X11 event accordingly.
    
    Supported events:
    
    ```c
    enum {
    	ON_KEYDOWN = 2,
    	ON_KEYUP = 3,
    	ON_MOUSEDOWN = 4,
    	ON_MOUSEUP = 5,
    	ON_MOUSEMOVE = 6,
    	ON_EXPOSE = 12,
    	ON_DESTROY = 17
    };
    
    // usage:
    mlx_hook(vars.win, ON_DESTROY, 0, close, &vars);
    ```
    
    # **X11 interface**
    
    X11 is the library that is used alongside of MiniLibX. It therefore is no secret that this header is very useful for finding all the according events of MiniLibX.
    
    ### **X11 events**
    
    There are a number of events to which you may describe.
    
    | Key | Event |  | Key | Event |  | Key | Event |
    | --- | --- | --- | --- | --- | --- | --- | --- |
    | 02 | KeyPress |  | 14 | NoExpose |  | 26 | CirculateNotify |
    | 03 | KeyRelease |  | 15 | VisibilityNotify |  | 27 | CirculateRequest |
    | 04 | ButtonPress |  | 16 | CreateNotify |  | 28 | PropertyNotify |
    | 05 | ButtonRelease |  | 17 | DestroyNotify |  | 29 | SelectionClear |
    | 06 | MotionNotify |  | 18 | UnmapNotify |  | 30 | SelectionRequest |
    | 07 | EnterNotify |  | 19 | MapNotify |  | 31 | SelectionNotify |
    | 08 | LeaveNotify |  | 20 | MapRequest |  | 32 | ColormapNotify |
    | 09 | FocusIn |  | 21 | ReparentNotify |  | 33 | ClientMessage |
    | 10 | FocusOut |  | 22 | ConfigureNotify |  | 34 | MappingNotify |
    | 11 | KeymapNotify |  | 23 | ConfigureRequest |  | 35 | GenericEvent |
    | 12 | Expose |  | 24 | GravityNotify |  | 36 | LASTEvent |
    | 13 | GraphicsExpose |  | 25 | ResizeRequest |  |  |  |
    
    ### **X11 masks**
    
    Each X11 event, also has a according mask. This way you can register to only one key when it triggers, or to all keys if you leave your mask to the default. Key masks therefore allow you to whitelist / blacklist events from your event subscriptions. The following masks are allowed:
    
    | Mask | Description |  | Mask | Description |
    | --- | --- | --- | --- | --- |
    | 0L | NoEventMask |  | (1L<<12) | Button5MotionMask |
    | (1L<<0) | KeyPressMask |  | (1L<<13) | ButtonMotionMask |
    | (1L<<1) | KeyReleaseMask |  | (1L<<14) | KeymapStateMask |
    | (1L<<2) | ButtonPressMask |  | (1L<<15) | ExposureMask |
    | (1L<<3) | ButtonReleaseMask |  | (1L<<16) | VisibilityChangeMask |
    | (1L<<4) | EnterWindowMask |  | (1L<<17) | StructureNotifyMask |
    | (1L<<5) | LeaveWindowMask |  | (1L<<18) | ResizeRedirectMask |
    | (1L<<6) | PointerMotionMask |  | (1L<<19) | SubstructureNotifyMask |
    | (1L<<7) | PointerMotionHintMask |  | (1L<<20) | SubstructureRedirectMask |
    | (1L<<8) | Button1MotionMask |  | (1L<<21) | FocusChangeMask |
    | (1L<<9) | Button2MotionMask |  | (1L<<22) | PropertyChangeMask |
    | (1L<<10) | Button3MotionMask |  | (1L<<23) | ColormapChangeMask |
    | (1L<<11) | Button4MotionMask |  | (1L<<24) | OwnerGrabButtonMask |
    
    # **Hooking into events**
    
    ### **mlx_hook**
    
    Hooking into events is one of the most powerful tools that MiniLibX provides. It allows you to register to any of the aforementioned events with the call of a simple hook registration function.
    
    To achieve this, we call the function `mlx_hook`.
    
    `void mlx_hook(mlx_win_list_t *win_ptr, int x_event, int x_mask, int (*f)(), void *param)`
    
    *Some version of mlbx doesn’t implement `x_mask` and whatever the value there will be no mask.*
    
    ### **Prototype of event functions**
    
    Event functions have a different prototype depending of the hooking event.
    
    | Hooking event | code | Prototype |
    | --- | --- | --- |
    | ON_KEYDOWN | 2 | int (*f)(int keycode, void *param) |
    | ON_KEYUP* | 3 | int (*f)(int keycode, void *param) |
    | ON_MOUSEDOWN* | 4 | int (*f)(int button, int x, int y, void *param) |
    | ON_MOUSEUP | 5 | int (*f)(int button, int x, int y, void *param) |
    | ON_MOUSEMOVE | 6 | int (*f)(int x, int y, void *param) |
    | ON_EXPOSE* | 12 | int (*f)(void *param) |
    | ON_DESTROY | 17 | int (*f)(void *param) |
    
    ### **Hooking alias**
    
    Minilibx api has some alias hooking function:
    
    - `mlx_expose_hook` function is an alias of mlx_hook on expose event (`12`).
    - `mlx_key_hook` function is an alias of mlx_hook on key up event (`3`).
    - `mlx_mouse_hook` function is an alias of mlx_hook on mouse down event (`4`).
    
    ### **Example**
    
    For example instead of calling `mlx_key_hook`, we can also register to the `KeyPress` and `KeyRelease` events. Lets take a look:
    
    ```c
    #include <mlx.h>
    
    typedef struct	s_vars {
    	void	*mlx;
    	void	*win;
    }				t_vars;
    
    int	close(int keycode, t_vars *vars)
    {
    	mlx_destroy_window(vars->mlx, vars->win);
    	return (0);
    }
    
    int	main(void)
    {
    	t_vars	vars;
    
    	vars.mlx = mlx_init();
    	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
    	mlx_hook(vars.win, 2, 1L<<0, close, &vars);
    	mlx_loop(vars.mlx);
    }
    ```
    
    Here we register to the `KeyPress`event with the according `KeyPressMask`. Now whenever we press a key, the window will be closed.
    
    Hooking is used for many purposes, including debugging and extending functionality. Examples might include intercepting keyboard or mouse event messages before they reach an application, or intercepting operating system calls in order to monitor behavior or modify the function of an application or another component. It is also widely used in benchmarking programs, for example to measure frame rate in 3D games, where the output and input is done through hooking. (trans)
    
    # **Hooking into key events**
    
    Hooking may sound difficult, but it really is not. Let’s take a look shall we?
    
    ```c
    #include <mlx.h>
    #include <stdio.h>
    
    typedef struct	s_vars {
    	void	*mlx;
    	void	*win;
    }				t_vars;
    
    int	key_hook(int keycode, t_vars *vars)
    {
    	printf("Hello from key_hook!\n");
    	return (0);
    }
    
    int	main(void)
    {
    	t_vars	vars;
    
    	vars.mlx = mlx_init();
    	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
    	mlx_key_hook(vars.win, key_hook, &vars);
    	mlx_loop(vars.mlx);
    }
    ```
    
    We have now registered a function that will print a message whenever we press a key. As you can see, we register a hook function with `mlx_key_hook`. However in the background it simply calls the function `mlx_hook`
     with the appropriate X11 event types. We will discuss this in the next chapter.
    
    # **Hooking into mouse events**
    
    ![https://harm-smits.github.io/42docs/libs/minilibx/res/mouse-schema.png](https://harm-smits.github.io/42docs/libs/minilibx/res/mouse-schema.png)
    
    Also, you can hook mouse events.
    
    ```c
    mlx_mouse_hook(vars.win, mouse_hook, &vars);
    ```
    
    Mouse code for MacOS:
    
    - Left click: 1
    - Right click: 2
    - Middle click: 3
    - Scroll up: 4
    - Scroll down : 5
    
    Now that you finally understand the basics of the MiniLibX library, we will start with drawing a tiny animation in the window. For this we will be using two new functions, namely `mlx_loop` and `mlx_loop_hook`.
    
    Loops are a feature of MiniLibX where it will continue to call your hook registered in `mlx_loop_hook` to render new frames, which you obviously have to pass to the window yourself.
    
    # **Hooking into loops**
    
    To initiate a loop, we call the `mlx_loop` function with the `mlx` instance as only parameter, take a look:
    
    ```c
    #include <mlx.h>
    
    int	main(void)
    {
    	void	*mlx;
    
    	mlx = mlx_init();
    	mlx_loop(mlx);
    }
    ```
    
    This will do nothing of course as we have no loop hook registered, therefore we will not be able to write anything to our frame.
    
    ```c
    #include <mlx.h>
    
    int	render_next_frame(void *YourStruct);
    
    int	main(void)
    {
    	void	*mlx;
    
    	mlx = mlx_init();
    	mlx_loop_hook(mlx, render_next_frame, YourStruct);
    	mlx_loop(mlx);
    }
    ```
    
    Now for each frame it requires, it will call the function `render_next_frame` with the parameter `YourStruct`. This will persist through multiple calls if it is a pointer, so use that to your advantage!
    
    # **Reading images**
    
    To read from a file to a image object, you need either the XMP or PNG format. In order to read we can call the functions `mlx_xpm_file_to_image` and `mlx_png_file_to_image` accordingly. Do mind that `mlx_png_file_to_image` currently leaks memory. Both functions accept exactly the same parameters and their usage is identical.
    
    ```c
    #include <mlx.h>
    
    int	main(void)
    {
    	void	*mlx;
    	void	*img;
    	char	*relative_path = "./test.xpm";
    	int		img_width;
    	int		img_height;
    
    	mlx = mlx_init();
    	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
    }
    ```
    
    If the `img` variable is equal to `NULL`, it means that the image reading has failed. It will also set the `img_width` and `img_height` accordingly, which is ideal when reading sprites. 
    
    The `mlx_xpm_to_image()`and `mlx_xpm_file_to_image()`functions will create a new image the same way. They will fill it using the specified `xpm_data`or `filename`, depending on which function is used. Note that MiniLibX does not use the standard Xpm library to deal with xpm images. You may not be able to read all types of xpm images. It does however, handle transparency.
    
    # **Using sync**
    
    We have three defines that we need to understand first:
    
    ```c
    #define MLX_SYNC_IMAGE_WRITABLE		1
    #define MLX_SYNC_WIN_FLUSH_CMD		2
    #define MLX_SYNC_WIN_CMD_COMPLETED	3
    
    int	mlx_sync(int cmd, void *ptr);
    ```
    
    `mlx_sync` ought to be called with the defined command codes. The first one, `MLX_SYNC_IMAGE_WRITABLE` will buffer all subsequential calls to an image (`ptr` is a pointer to the MLX image object). If you want to propagate changes, you will have to flush the window in which the image is present, using `MLX_SYNC_WIN_FLUSH_CMD` and the window you want to flush as a `ptr`.
    

**Draw Wall :**

**Texture :** 

To us, a texture is a flat, 2D picture that gets applied to the polygons that make up the 3D structures in the viewed frame. To a computer, though, it's nothing more than a small block of memory, in the form of a 2D array. Each entry in the array represents a color value for one of the pixels in the texture image (better known as *texels -* texture pixels).
