/***************************************************************************************************
 * Daniel Wiese
 * CS50 - Harvard
 * PSET 3 - breakout.c
 * Fall 2014
 * Due: Thursday 02-Oct (noon)
 ***************************************************************************************************
 *
 **************************************************************************************************/

// Standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400
#define PADDLE_WIDTH 100
#define PADDLE_THICKNESS 10
#define BLOCK_SPACING 2
#define PADDLE_SPACING_Y 20
#define BALL_RADIUS 20
#define INIT_VELOCITY 2.0
#define PADDLE_PADDING 5

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// lives
#define INIT_LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
GLabel initLivesboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
void updateLivesboard(GWindow window, GLabel label, int lives);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel lives_label = initLivesboard(window);
    GLabel points_label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = INIT_LIVES;

    // number of points initially
    int points = 0;

    // initial velocity
    double xvelocity = (int) ((drand48() - 0.5) * 1.5 * INIT_VELOCITY);
    if (xvelocity < 0.4 && xvelocity >= 0)
    {
        xvelocity = xvelocity + 0.4;
    }
    else if (xvelocity > -0.4 && xvelocity <0)
    {
        xvelocity = xvelocity - 0.4;
    }

    double yvelocity = INIT_VELOCITY;

    // Add stuff to window
    add(window, paddle);
    add(window, points_label);
    add(window, lives_label);
    add(window, ball);

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // move ball
        move(ball, xvelocity, yvelocity);

        // bounce off right edge of window
        if (getX(ball) + 2 * BALL_RADIUS >= WIDTH)
        {
            xvelocity = - xvelocity;
        }
        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            xvelocity = - xvelocity;
        }
        // bounce ball off of top of window
        if (getY(ball) <= 0)
        {
            yvelocity = - yvelocity;
        }
        // bounce ball off of bottom of window
        if (getY(ball) + 2 * BALL_RADIUS >= HEIGHT)
        {
            yvelocity = - yvelocity;
            lives--;
            updateLivesboard(window, lives_label, lives);
        }

        // Check to see if the ball hit anything
        GObject object = detectCollision(window, ball);

        // If the object is not null (ie collision with some object occured)
        if (object)
        {
            // Check that the collision was with rectangle (paddle or block)
            if (strcmp(getType(object),"GRect") == 0)
            {
                // if it was paddle, bounce ball off
                if (object == paddle)
                {
                yvelocity = - yvelocity;
                }
                // if it was block, bounce ball off, add a point to score, and remove block
                else
                {
                removeGWindow(window, object);
                yvelocity = - yvelocity;
                points++;
                updateScoreboard(window, points_label, points);
                }
            }
        }

        // linger before moving again
        pause(10);

        // THE FOLLOWING CODE CONTINUALLY MOVES THE PADDLE WITH THE MOUSE
        GEvent event = getNextEvent(MOUSE_EVENT);

        // Check to see if there was an event of mouse moving
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // Make paddle follow cursor
                double x = getX(event) - getWidth(paddle) / 2;
                setLocation(paddle, x, HEIGHT - PADDLE_SPACING_Y);
            }
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/** Initializes window with a grid of bricks. */
void initBricks(GWindow window)
{
    int blockwidth = WIDTH / COLS;
    int blockheight = HEIGHT / (4 * ROWS);

    for (int i = 0; i <= COLS; i++)
    {
        for (int j = 0; j <= ROWS; j++)
        {
            GRect rect = newGRect(i * blockwidth + BLOCK_SPACING, j * blockheight + BLOCK_SPACING, blockwidth - 2 * BLOCK_SPACING, blockheight - 2 * BLOCK_SPACING);
            setFilled(rect, true);
            setColor(rect, "RED");
            add(window, rect);
        }
    }
}

/* Instantiates ball in center of window.  Returns ball. */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH / 2 - BALL_RADIUS, HEIGHT / 2 - BALL_RADIUS, 2 * BALL_RADIUS, 2 * BALL_RADIUS);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    // add(window, paddle);
    return ball;
}

/* Instantiates paddle in bottom-middle of window. */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect((getWidth(window) - PADDLE_WIDTH)/ 2, getHeight(window) - PADDLE_SPACING_Y, PADDLE_WIDTH, PADDLE_THICKNESS);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    return paddle;
}

/* Instantiates, configures, and returns label for scoreboard. */
GLabel initScoreboard(GWindow window)
{
    // Create and initialize label with initial number of lives
    GLabel label = newGLabel("");
    char s[12];
    sprintf(s, "Points: %d", 0);
    setLabel(label, s);
    setFont(label, "SansSerif-72");
    setColor(label, "GRAY");

    // Center label
    double x = (WIDTH - getWidth(label)) / 2;
    double y = (HEIGHT - getHeight(label)) / 2;
    setLocation(label, x, y);
    return label;
}

/* Instantiates, configures, and returns label for livesboard.
* I copied and pasted this because it made more sense to have lives displayed
* if I am giving 1 point per brick and I didn't want to change the given code per instructions*/
GLabel initLivesboard(GWindow window)
{
    // Create and initialize label with initial number of lives
    GLabel label = newGLabel("");
    char s[12];
    sprintf(s, "Lives: %d", INIT_LIVES);
    setLabel(label, s);
    setFont(label, "SansSerif-72");
    setColor(label, "GRAY");

    // Center label
    double x = (WIDTH - getWidth(label)) / 2;
    double y = (HEIGHT + 120 - getHeight(label)) / 2;
    setLocation(label, x, y);
    return label;
}

/* Updates scoreboard's label, keeping it centered in window. */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "Points: %i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/* Updates livesboard's label, keeping it centered in window.
* again, it made more sense to display lives instead of points */
void updateLivesboard(GWindow window, GLabel label, int lives)
{
    // update label
    char s[12];
    sprintf(s, "Lives: %i", lives);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) + 120 - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * BALL_RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * BALL_RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * BALL_RADIUS, y + 2 * BALL_RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}

/*        // bounce ball off of paddle*/
/*        if (getY(ball) + 2 * BALL_RADIUS >= HEIGHT - PADDLE_SPACING_Y && */
/*            getX(ball) + BALL_RADIUS >= getX(paddle) - PADDLE_PADDING && */
/*            getX(ball) + BALL_RADIUS <= getX(paddle) + PADDLE_WIDTH + PADDLE_PADDING)*/
/*        {*/
/*            yvelocity = - yvelocity;*/
/*        }*/
