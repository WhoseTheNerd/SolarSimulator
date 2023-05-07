#include "Planet.hpp"

#include <random>

namespace SolarSim {

    constexpr float G = 6.67430e-11;
    constexpr float TIMESTEP = 3600.0f * 24.0f;
    constexpr float AU = 149.6e9;
    constexpr float SCALE = 200.0f / AU;

    Planet::Planet(const std::string& name, const Pandora::Ref<Pandora::Mesh>& mesh, const Pandora::Ref<Pandora::Texture2D>& texture, double mass, double radius, double distance, double orbit_velocity)
        : m_Name(name), Pandora::Entity(mesh, texture), m_Mass(mass), m_Radius(radius), m_Velocity(glm::dvec2{0.0, orbit_velocity}), m_AstroPos(glm::dvec2{distance, 0.0})
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<double> dist(0.0, 2.0*3.14);

        const double angle = dist(gen);
        /*m_AstroPos.x *= std::cos(angle);
        m_AstroPos.y *= std::sin(angle);*/

        m_Velocity.x = -orbit_velocity * std::sin(angle);
        m_Velocity.y = orbit_velocity * std::cos(angle);

        m_Position = glm::vec3{m_AstroPos.x * SCALE, 0.0f, m_AstroPos.y * SCALE};
        m_Scale = glm::vec3{radius / 1000.0f};
        CalculateModelMatrix();

        PD_TRACE("Planet {}", name);
        PD_TRACE("X: {}; Y: {}", m_AstroPos.x, m_AstroPos.y);
        PD_TRACE("VelX: {}; VelY: {}", m_Velocity.x, m_Velocity.y);
    }

    bool Planet::operator==(const Planet& other) const
    {
        return m_Mass == other.m_Mass && m_Radius == other.m_Radius;
    }

    bool Planet::operator!=(const Planet& other) const
    {
        return !(*this == other);
    }

    void Planet::OnUpdate(const std::vector<Pandora::Ref<Planet>>& planets)
    {
        double total_fx = 0.0f;
        double total_fy = 0.0f;

        for (const auto& planet : planets) {
            if (*planet != *this) {
                const glm::dvec2 diff = this->m_AstroPos - planet->m_AstroPos;
                const double distance_x = diff.x;
                const double distance_y = diff.y;

                const double distance = std::sqrt(distance_x*distance_x + distance_y*distance_y);
                const double distance_squared = distance * distance;

                const double planet_mass = planet->m_Mass;
                const double current_mass = m_Mass;
                const double force = G * current_mass * planet_mass / distance_squared;
                const double theta = std::atan2(distance_y, distance_x);
                const double force_x = std::cos(theta) * force;
                const double force_y = std::sin(theta) * force;

                if (std::isnan(distance) || std::isnan(force) || std::isinf(distance) || std::isinf(force)) {
                    PD_DEBUGBREAK();
                }

                total_fx += force_x;
                total_fy += force_y;
            }
        }


        m_Velocity.x += total_fx / m_Mass * TIMESTEP;
        m_Velocity.y += total_fy / m_Mass * TIMESTEP;

        m_AstroPos.x += m_Velocity.x * TIMESTEP;
        m_AstroPos.y += m_Velocity.y * TIMESTEP;
        
        m_Position = glm::vec3{m_AstroPos.x * SCALE, 0.0f, m_AstroPos.y * SCALE};
        CalculateModelMatrix();
    }
}