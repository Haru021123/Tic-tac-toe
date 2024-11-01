// Example of replacing the first tab content
import React from 'react';
import { createBottomTabNavigator } from '@react-navigation/bottom-tabs';
import { View, Text } from 'react-native';
import GameBoard from '../GameBoard';

const Tab = createBottomTabNavigator();

const MyTabs = () => {
  return (
    <Tab.Navigator>
      <Tab.Screen name="Game" component={GameBoard} />
      <Tab.Screen name="Explore" component={ExploreScreen} />
    </Tab.Navigator>
  );
};

const ExploreScreen = () => (
  <View>
    <Text>Explore Screen</Text>
  </View>
);

export default MyTabs;
