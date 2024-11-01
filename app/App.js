// App.js
import React from 'react';
import { SafeAreaView, StatusBar } from 'react-native';
import GameBoard from './GameBoard';

export default function App() {
  return (
    <SafeAreaView style={{ flex: 1 }}>
      <StatusBar barStyle="dark-content" />
      <GameBoard />
    </SafeAreaView>
  );
}
