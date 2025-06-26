// Entity.h
#pragma once
#include <SDL2/SDL.h>
#include <SDL_rect.h>

/**
 * @class Entity
 * @brief Abstract base class representing any drawable and updatable game object.
 *
 * Provides a common interface for all game entities, including position management,
 * rendering, bounding box retrieval, and destruction state.
 */
class Entity {
public:
    /** Virtual destructor for safe polymorphic cleanup */
    virtual ~Entity() = default;

    /**
     * @brief Render the entity to the screen.
     *
     * Must be implemented by derived classes to draw the entity using graphics context.
     */
    virtual void render() = 0;

    /**
     * @brief Get the bounding rectangle of the entity.
     *
     * Used for collision detection and positioning logic.
     *
     * @return SDL_FRect representing the bounds of the entity.
     */
    virtual SDL_FRect getBounds() const = 0;

    /**
     * @brief Get the bounding rectangle of the entity.
     *
     * Used for collision detection and positioning logic.
     *
     * @return SDL_FRect representing the bounds of the entity.
     */
    virtual void setPosition(float x, float y) { position = {x, y}; }

    /**
     * @brief Get the current position of the entity.
     * @return SDL_FPoint representing the current position.
     */
    virtual SDL_FPoint getPosition() const { return position; }

    /**
     * @brief Check if the entity is destroyed.
     * @return True if destroyed, false otherwise. Default is false.
     */
    virtual bool isDestroyed() const {return false; }

    /** Mark the entity as destroyed. Default does nothing. */
    virtual void destroy() {}

protected:
    SDL_FPoint position{0.0f, 0.0f};  ///< Current position of the entity.
};
