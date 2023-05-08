#pragma once

#include <Pandora.hpp>

namespace SolarSim {

    class Planet : public Pandora::Entity
    {   
    public:
        Planet(const std::string& name, const Pandora::Ref<Pandora::Mesh>& mesh, const Pandora::Ref<Pandora::Texture2D>& texture, double mass, double radius, double distance, double orbit_velocity, double rotationRate, const glm::vec3& axis);

        bool operator==(const Planet& other) const;
        bool operator!=(const Planet& other) const;

        void OnUpdate(Pandora::Timestep ts, const std::vector<Pandora::Ref<Planet>>& planets);

        const std::string& GetName() const { return m_Name; }
        double GetRadius() const { return m_Radius; }
    private:
        std::string m_Name;
        double m_Mass;
        double m_Radius;
        double m_RotationRate;
        glm::vec3 m_Axis;
        glm::dvec2 m_AstroPos;
        glm::dvec2 m_Velocity;
    };
}
