// Include gazebo
#include <gazebo/gazebo.hh>

// Gazebo namespace
namespace gazebo {

    // Create a class that inherites the WorldPlugin class within gazebo
    class WorldPluginMyRobot : public WorldPlugin {

        // Constructor function
        public: WorldPluginMyRobot() : WorldPlugin() {

            // Print something
            std::cout << "Welcome to Udacity Office!!" << std::endl;

        }

        // Load function (mandetory) to recieve info from world file
        public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf) {

        }

    };

    // Register the plugin in the simulator
    GZ_REGISTER_WORLD_PLUGIN(WorldPluginMyRobot)

}