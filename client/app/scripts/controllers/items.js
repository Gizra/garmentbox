'use strict';

/**
 * @ngdoc function
 * @name clientApp.controller:MainCtrl
 * @description
 * # MainCtrl
 * Controller of the clientApp
 */
angular.module('clientApp')
  .controller('ItemsCtrl', function ($scope, Items, ItemVariants, $state, $log) {

    // Initialize values.
    $scope.items = null;
    $scope.selectedItem = null;
    $scope.loadingItems = false;

    $scope.itemVariants = null;
    $scope.selectedItemVariants = null;
    $scope.loadingItemVariants = false;

    $scope.$on('$stateChangeSuccess', function(event, toState, toParams){
      if (!$state.includes('dashboard.items')) {
        return;
      }

      // Load items.
      $scope.loadingItems = true;
      Items.get().then(function(items) {
        $scope.loadingItems = false;
        $scope.items = items;

        if (toParams.id) {
          setSelectedItem(toParams.id);
        }

        if (toParams.variant) {
          setSelectedItemVariant(toParams.variant);
        }
      });
    });

    /**
     * Set the selected item.
     *
     * @param int id
     *   The item ID.
     */
    var setSelectedItem = function(id) {
      $scope.selectedItem = null;

      angular.forEach($scope.items, function(value) {
        if (value.id == id) {
          $scope.selectedItem = value;
        }
      });

      $scope.loadingItemVariants = true;
      ItemVariants.get(id).then(function(itemVariants) {
        $scope.loadingItemVariants = false;
        $scope.itemVariants = itemVariants;
      });
    };

    /**
     * Set the selected item variant.
     *
     * @param int id
     *   The item variant ID.
     */
    var setSelectedItemVariant = function(id) {
      $scope.selectedItemVariant = null;

      ItemVariants.get(id).then(function(itemVariants) {
        angular.forEach($scope.itemVariants, function(value) {
          if (value.id == id) {
            $scope.selectedItemVariant = value;
          }
        });
      });
    }
  });
