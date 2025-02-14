<?php

namespace Rector\Tests\DowngradePhp74\Rector\Array_\DowngradeArraySpreadRector\Fixture;

use ArrayIterator;

class WithIterablePseudotypeFunctionItemClass
{
    function getIterable(): iterable
    {
        return new ArrayIterator(['apple', 'pear']);
    }

    public function run()
    {
        $fruits = ['banana', 'orange', ...$this->getIterable(), 'watermelon'];
    }
}

?>
-----
<?php

namespace Rector\Tests\DowngradePhp74\Rector\Array_\DowngradeArraySpreadRector\Fixture;

use ArrayIterator;

class WithIterablePseudotypeFunctionItemClass
{
    function getIterable(): iterable
    {
        return new ArrayIterator(['apple', 'pear']);
    }

    public function run()
    {
        $item2Unpacked = $this->getIterable();
        $fruits = array_merge(['banana', 'orange'], is_array($item2Unpacked) ? $item2Unpacked : iterator_to_array($item2Unpacked), ['watermelon']);
    }
}

?>
