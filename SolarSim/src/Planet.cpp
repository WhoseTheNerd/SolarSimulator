#include "Planet.hpp"

namespace SolarSim {

    constexpr float G = 6.67430e-11;
    constexpr float TIMESTEP = 3600.0f * 24.0f;
    constexpr float AU = 149.6e9;
    constexpr float SCALE = 20'000.0f / AU;

    Planet::Planet(const std::string& name, const Pandora::Ref<Pandora::Mesh>& mesh, const Pandora::Ref<Pandora::Texture2D>& texture, double mass, double radius, double distance, double orbit_velocity)
        : m_Name(name), Pandora::Entity(mesh, texture), m_Mass(mass), m_Radius(radius), m_Velocity(glm::dvec2{0.0, orbit_velocity}), m_AstroPos(glm::dvec2{distance, 0.0})
    {
        m_Position = glm::vec3{m_AstroPos.x * SCALE, 0.0f, m_AstroPos.y * SCALE};
        m_Scale = glm::vec3{radius / 100'000.0f};
        CalculateModelMatrix();
    }

    bool Planet::operator==(const Planet& other) const
    {
        return m_Mass == other.m_Mass && m_Radius == other.m_Radius;
    }

    bool Planet::operator!=(const Planet& other) const
    {
        return !(*this == other);
    }

    void Planet::OnUpdate(Pandora::Timestep ts, const std::vector<Pandora::Ref<Planet>>& planets)
    {
        double total_fx = 0.0f;
        double total_fy = 0.0f;

        for (const auto& planet : planets) {
            if (*planet != *this) {
                const glm::dvec2 diff = planet->m_AstroPos - this->m_AstroPos;
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


        m_Velocity.x += total_fx / m_Mass * TIMESTEP * ts;
        m_Velocity.y += total_fy / m_Mass * TIMESTEP * ts;

        m_AstroPos.x += m_Velocity.x * TIMESTEP * ts;
        m_AstroPos.y += m_Velocity.y * TIMESTEP * ts;
        
        m_Position = glm::vec3{m_AstroPos.x * SCALE, 0.0f, m_AstroPos.y * SCALE};
        CalculateModelMatrix();
    }
}