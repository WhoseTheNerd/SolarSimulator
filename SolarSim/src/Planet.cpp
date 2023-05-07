#include "Planet.hpp"

namespace SolarSim {

    constexpr float G = 6.67430e-11;
    constexpr float TIMESTEP = 3600.0f * 24.0f;
    constexpr float AU = 149.6e9;
    constexpr float SCALE = 20'000.0f / AU;

    Planet::Planet(const std::string& name, const Pandora::Ref<Pandora::Mesh>& mesh, const Pandora::Ref<Pandora::Texture2D>& texture, double mass, double radius, double distance, double orbit_velocity, double rotationRate, const glm::vec3& axis)
        : m_Name(name), Pandora::Entity(mesh, texture), m_Mass(mass), m_Radius(radius), m_Velocity(glm::dvec2{0.0, orbit_velocity}), m_AstroPos(glm::dvec2{distance, 0.0}), m_RotationRate(rotationRate), m_Axis(axis)
    {
        m_Position = glm::vec3{m_AstroPos.x * SCALE, 0.0f, m_AstroPos.y * SCALE};
        m_Scale = glm::vec3{static_cast<float>(radius) / 100'000.0f};
        AddRotation(axis);
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
        auto CalculateAttraction = [](const Planet& left, const Planet& right) -> glm::dvec2 {
            const glm::dvec2 diff = left.m_AstroPos - right.m_AstroPos;
            const double distance_squared = glm::dot(diff, diff);

            const double force = G * right.m_Mass * left.m_Mass / distance_squared;
            const double theta = std::atan2(diff.y, diff.x);
            const double force_x = std::cos(theta) * force;
            const double force_y = std::sin(theta) * force;

            PD_ASSERT(!(std::isnan(distance_squared) || std::isnan(force) || std::isinf(distance_squared) || std::isinf(force)), "Distance or force cannot be NaN or Inf!");

            return glm::dvec2{force_x, force_y};
        };

        #if 1
        glm::dvec2 total_force{};
        for (const auto& planet : planets) {
            if (*planet != *this) {
                total_force += CalculateAttraction(*planet, *this);
            }
        }
        #else
        const glm::dvec2 total_force = std::accumulate(std::begin(planets), std::end(planets), glm::dvec2{0.0}, [&](auto&& total, const auto& planet){
            if (*planet != *this) {
                return total + CalculateAttraction(*planet, *this);
            }
            return total;
        });
        #endif

        m_Velocity.x += total_force.x / m_Mass * TIMESTEP * ts;
        m_Velocity.y += total_force.y / m_Mass * TIMESTEP * ts;

        m_AstroPos.x += m_Velocity.x * TIMESTEP * ts;
        m_AstroPos.y += m_Velocity.y * TIMESTEP * ts;
        
        m_Position.x = m_AstroPos.x * SCALE; 
        m_Position.z = m_AstroPos.y * SCALE;

        AddRotation(m_RotationRate * ts, glm::vec3{0, 1, 0});
        CalculateModelMatrix();
    }
}